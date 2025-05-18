// dbFilepath.h
#ifndef DBFILEPATH_H
#define DBFILEPATH_H

#include "dbManager.h"
#include "FilePathInfo.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include <QStringList>
#include <QVariantMap>

class DbTransactionGuard {
public:
    DbTransactionGuard(QSqlDatabase& db);
    ~DbTransactionGuard();
    void commit();
private:
    QSqlDatabase& db;
    bool committed;
};

class dbFilepath : public dbManager {
public:
    explicit dbFilepath(const QString &dbName);
    ~dbFilepath() override;

    bool insertFilePath(const QString &filePath, int &fileId);
    bool getFileId(const QString &filePath, int &fileId);
    QList<FilePathInfo> searchFiles(const QString &keyword);
    QStringList getAllFilePaths();
    bool updateTags(int fileId, const QString &tag);
    bool updateAnnotation(int fileId, const QString &annotation);
    void updateExpirationDate(int fileId, const QDateTime &dateTime);
    bool deleteFileEntry(int fileId);
    bool updateFilePath(const QString &newFilePath, const QString &oldFilePath);
    bool updateFileInfo(const FilePathInfo& info);
    bool hasFile(const QString &filePath) const;
    QStringList getAllTags();
    QList<FilePathInfo> getFilePathsByTag(const QString &tag);
    bool getTags(int fileId, QStringList &tags);
    bool getAnnotation(int fileId, QString &annotation);
    bool getFileInfoByFilePath(const QString& filePath, FilePathInfo& info);

private:
    bool executePrepared(QSqlQuery& query, const QString& sql, const QVariantMap& params);
    void logDbError(const QString& context, const QSqlQuery& query) const;
};

#endif // DBFILEPATH_H
