// dbFilepath.h
#ifndef DBFILEPATH_H
#define DBFILEPATH_H

#include "dbManager.h"
#include "FilePathInfo.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include <QStringList>
#include <QDateTime>
#include <QVariantMap>

class DbTransactionGuard {
public:
    DbTransactionGuard(QSqlDatabase& db) : db(db), committed(false) { db.transaction(); }
    ~DbTransactionGuard() { if (!committed) db.rollback(); }
    void commit() { db.commit(); committed = true; }
private:
    QSqlDatabase& db;
    bool committed;
};

class dbFilepath : public dbManager {
public:
    explicit dbFilepath(const QString &dbName) : dbManager(dbName) {}
    ~dbFilepath() override {}

    bool insertFilePath(const QString &filePath, int &fileId) {
        QSqlQuery query(dbsqlite);
        QVariantMap params = {{":filePath", filePath}};
        if (!executePrepared(query, "INSERT INTO FilePaths (file_path) VALUES (:filePath)", params)) return false;
        fileId = query.lastInsertId().toInt();
        return true;
    }

    bool getFileId(const QString &filePath, int &fileId) {
        QSqlQuery query(dbsqlite);
        QVariantMap params = {{":filePath", filePath}};
        if (executePrepared(query, "SELECT id FROM FilePaths WHERE file_path = :filePath", params) && query.next()) {
            fileId = query.value(0).toInt();
            return true;
        }
        return false;
    }

    QList<FilePathInfo> searchFiles(const QString &keyword) {
        QList<FilePathInfo> fileInfos;
        QSqlQuery query(dbsqlite);
        QVariantMap params = {{":keyword", "%" + keyword + "%"}};
        QString sql = "SELECT DISTINCT fp.file_path, t.tag_name, fp.expiration_date, t.annotation "
                      "FROM FilePaths fp LEFT JOIN Tags t ON fp.id = t.file_id "
                      "WHERE fp.file_path LIKE :keyword OR t.tag_name LIKE :keyword";
        if (!executePrepared(query, sql, params)) return fileInfos;

        while (query.next()) {
            fileInfos.append({query.value(0).toString(), query.value(1).toString(),
                              query.value(2).toDateTime(), query.value(3).toString()});
        }
        return fileInfos;
    }

    QStringList getAllFilePaths() {
        QStringList paths;
        if (!open()) return paths;
        QSqlQuery query(dbsqlite);
        if (!query.exec("SELECT file_path FROM FilePaths")) return paths;
        while (query.next()) paths << query.value(0).toString();
        return paths;
    }

    bool updateTags(int fileId, const QString &tag) {
        QSqlQuery query(dbsqlite);
        query.prepare("DELETE FROM Tags WHERE file_id = :fileId");
        query.bindValue(":fileId", fileId);
        if (!query.exec()) return false;

        query.prepare("INSERT INTO Tags (file_id, tag_name) VALUES (:fileId, :tagName)");
        query.bindValue(":fileId", fileId);
        query.bindValue(":tagName", tag.trimmed());
        return query.exec();
    }

    bool updateAnnotation(int fileId, const QString &annotation) {
        QSqlQuery query(dbsqlite);
        query.prepare("INSERT OR REPLACE INTO Annotations (file_id, annotation) VALUES (:fileId, :annotation)");
        query.bindValue(":fileId", fileId);
        query.bindValue(":annotation", annotation);
        return query.exec();
    }

    void updateExpirationDate(int fileId, const QDateTime &dateTime) {
        QSqlQuery query(dbsqlite);
        query.prepare("UPDATE FilePaths SET expiration_date = :expiration_date WHERE id = :file_id");
        query.bindValue(":expiration_date", dateTime);
        query.bindValue(":file_id", fileId);
        query.exec();
    }

    bool deleteFileEntry(int fileId) {
        DbTransactionGuard guard(dbsqlite);
        QSqlQuery query(dbsqlite);

        QVariantMap params = {{":file_id", fileId}};
        if (!executePrepared(query, "DELETE FROM Tags WHERE file_id = :file_id", params) ||
            !executePrepared(query, "DELETE FROM Annotations WHERE file_id = :file_id", params) ||
            !executePrepared(query, "DELETE FROM FilePaths WHERE id = :file_id", params)) {
            return false;
        }
        guard.commit();
        return true;
    }

    bool updateFilePath(const QString &newFilePath, const QString &oldFilePath) {
        QSqlQuery query(dbsqlite);
        QVariantMap params = {{":newFilePath", newFilePath}, {":oldFilePath", oldFilePath}};
        return executePrepared(query, "UPDATE FilePaths SET file_path = :newFilePath WHERE file_path = :oldFilePath", params);
    }

    bool updateFileInfo(const FilePathInfo& info) {
        DbTransactionGuard guard(dbsqlite);
        QSqlQuery query(dbsqlite);

        QVariantMap updateMap = {{":expiration_date", info.expirationDate.toString("yyyy-MM-dd HH:mm:ss")},
                                 {":file_path", info.filePath}};
        if (!executePrepared(query, "UPDATE FilePaths SET expiration_date = :expiration_date WHERE file_path = :file_path", updateMap)) return false;

        int fileId = -1;
        if (!getFileId(info.filePath, fileId)) return false;

        if (!updateTags(fileId, info.tagName) || !updateAnnotation(fileId, info.annotation)) return false;
        guard.commit();
        return true;
    }

    bool hasFile(const QString &filePath) const {
        QSqlQuery query(dbsqlite);
        QVariantMap params = {{":filePath", filePath}};
        if (!const_cast<dbFilepath*>(this)->executePrepared(query, "SELECT COUNT(*) FROM FilePaths WHERE file_path = :filePath", params)) return false;
        return query.next() && query.value(0).toInt() > 0;
    }

    QStringList getAllTags() {
        QStringList tags;
        QSqlQuery query(dbsqlite);
        if (query.exec("SELECT DISTINCT tag_name FROM Tags")) {
            while (query.next()) tags << query.value(0).toString();
        }
        return tags;
    }

    QList<FilePathInfo> getFilePathsByTag(const QString &tag) {
        QList<FilePathInfo> list;
        QSqlQuery query(dbsqlite);

        QString sql;
        QVariantMap params;
        if (tag == "刷新") {
            sql = "SELECT DISTINCT fp.file_path, t.tag_name, fp.expiration_date, a.annotation FROM FilePaths fp "
                  "LEFT JOIN Tags t ON fp.id = t.file_id LEFT JOIN Annotations a ON fp.id = a.file_id";
        } else {
            sql = "SELECT DISTINCT fp.file_path, t.tag_name, fp.expiration_date, a.annotation FROM FilePaths fp "
                  "LEFT JOIN Tags t ON fp.id = t.file_id LEFT JOIN Annotations a ON fp.id = a.file_id WHERE t.tag_name = :tag";
            params[":tag"] = tag;
        }

        if (!executePrepared(query, sql, params)) return list;

        while (query.next()) {
            list.append({query.value(0).toString(), query.value(1).toString(),
                         query.value(2).toDateTime(), query.value(3).toString()});
        }
        return list;
    }

    bool getTags(int fileId, QStringList &tags) {
        QSqlQuery query(dbsqlite);
        QVariantMap params = {{":fileId", fileId}};
        if (!executePrepared(query, "SELECT tag_name FROM Tags WHERE file_id = :fileId", params)) return false;
        while (query.next()) tags << query.value(0).toString();
        return true;
    }

    bool getAnnotation(int fileId, QString &annotation) {
        QSqlQuery query(dbsqlite);
        QVariantMap params = {{":fileId", fileId}};
        if (executePrepared(query, "SELECT annotation FROM Annotations WHERE file_id = :fileId", params) && query.next()) {
            annotation = query.value(0).toString();
            return true;
        }
        return false;
    }

    bool getFileInfoByFilePath(const QString& filePath, FilePathInfo& info) {
        DbTransactionGuard guard(dbsqlite);
        QSqlQuery query(dbsqlite);
        QVariantMap params = {{":file_path", filePath}};

        if (!executePrepared(query, "SELECT expiration_date FROM FilePaths WHERE file_path = :file_path", params) || !query.next()) return false;
        info.filePath = filePath;
        info.expirationDate = QDateTime::fromString(query.value(0).toString(), "yyyy-MM-dd'T'HH:mm:ss.zzz");

        if (!executePrepared(query, "SELECT tag_name FROM Tags WHERE file_id = (SELECT id FROM FilePaths WHERE file_path = :file_path)", params) || !query.next()) return false;
        info.tagName = query.value(0).toString();

        if (!executePrepared(query, "SELECT annotation FROM Annotations WHERE file_id = (SELECT id FROM FilePaths WHERE file_path = :file_path)", params) || !query.next()) return false;
        info.annotation = query.value(0).toString();

        guard.commit();
        return true;
    }

private:
    bool executePrepared(QSqlQuery& query, const QString& sql, const QVariantMap& params) {
        if (!query.prepare(sql)) return false;
        for (auto it = params.begin(); it != params.end(); ++it) query.bindValue(it.key(), it.value());
        return query.exec();
    }

    void logDbError(const QString& context, const QSqlQuery& query) const {
        qWarning() << context << ":" << query.lastError().text();
    }
};

#endif // DBFILEPATH_H
