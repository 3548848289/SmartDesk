#include "DBSQlite.h"
#include <QUuid>

DBSQlite::DBSQlite(const QString &dbName) {
    QString connectionName = "sqlite_" + QUuid::createUuid().toString();
    dbsqlite = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    dbsqlite.setDatabaseName(dbName);

    if (!dbsqlite.open()) {
        qDebug() << "数据库连接初始化失败:" << dbsqlite.lastError().text();
    }
}

DBSQlite::~DBSQlite() {
    close();
}

bool DBSQlite::open() {
    if (!dbsqlite.isOpen()) {
        if (!dbsqlite.open()) {
            qDebug() << "数据库连接失败：" << dbsqlite.lastError().text();
            return false;
        }
        initializeDatabase();
    }
    return true;
}

void DBSQlite::close() {
    if (dbsqlite.isOpen()) {
        QSqlQuery().finish();
        dbsqlite.close();
    }
    QSqlDatabase::removeDatabase(dbsqlite.connectionName());
}

QString DBSQlite::lastError() const {
    return dbsqlite.lastError().text();
}

void DBSQlite::initializeDatabase() {
    QSqlQuery query(dbsqlite);

    query.exec("CREATE TABLE IF NOT EXISTS FilePaths "
               "(id INTEGER PRIMARY KEY, file_path TEXT UNIQUE, expiration_date DATE)");
    query.exec("CREATE TABLE IF NOT EXISTS Tags "
               "(id INTEGER PRIMARY KEY, file_id INTEGER, tag_name TEXT, FOREIGN KEY(file_id) REFERENCES FilePaths(id))");
    query.exec("CREATE TABLE IF NOT EXISTS Annotations "
               "(id INTEGER PRIMARY KEY, file_id INTEGER, annotation TEXT, FOREIGN KEY(file_id) REFERENCES FilePaths(id))");


}

bool DBSQlite::addFilePath(const QString &filePath, int &fileId) {
    QSqlQuery query(dbsqlite);
    query.prepare("INSERT INTO FilePaths (file_path) VALUES (:filePath)");
    query.bindValue(":filePath", filePath);

    if (!query.exec()) {
        qDebug() << "插入文件路径失败：" << query.lastError().text();
        return false;
    }
    fileId = query.lastInsertId().toInt();
    return true;
}

bool DBSQlite::getFileId(const QString &filePath, int &fileId) {
    QSqlQuery query(dbsqlite);

    query.prepare("SELECT id FROM FilePaths WHERE file_path = :filePath");
    query.bindValue(":filePath", filePath);

    if (query.exec() && query.next()) {
        fileId = query.value(0).toInt();
        return true;
    }
    return false;
}

bool DBSQlite::getTags(int fileId, QStringList &tags) {
        QSqlQuery query(dbsqlite);

    query.prepare("SELECT tag_name FROM Tags WHERE file_id = :fileId");
    query.bindValue(":fileId", fileId);

    if (query.exec()) {
        while (query.next())
            tags.append(query.value(0).toString());
        return true;
    }
    return false;
}

bool DBSQlite::getAnnotation(int fileId, QString &annotation) {
     QSqlQuery query(dbsqlite);

    query.prepare("SELECT annotation FROM Annotations WHERE file_id = :fileId");
    query.bindValue(":fileId", fileId);

    if (query.exec() && query.next()) {
        annotation = query.value(0).toString();
        return true;
    }
    return false;
}

bool DBSQlite::saveTags(int fileId, const QStringList &tags) {
        QSqlQuery query(dbsqlite);

    query.prepare("DELETE FROM Tags WHERE file_id = :fileId");
        for (const QString &tag : tags) {
            query.prepare("INSERT INTO Tags (file_id, tag_name) VALUES (:fileId, :tagName)");
            query.bindValue(":fileId", fileId);
            query.bindValue(":tagName", tag);
            query.exec();
        }
    query.bindValue(":fileId", fileId);
    query.exec();

    return true;
}

bool DBSQlite::saveAnnotation(int fileId, const QString &annotation) {
        QSqlQuery query(dbsqlite);

    query.prepare("INSERT OR REPLACE INTO Annotations (file_id, annotation) VALUES (:fileId, :annotation)");
    query.bindValue(":fileId", fileId);
    query.bindValue(":annotation", annotation);
    return query.exec();
}

bool DBSQlite::hasTagsForFile(const QString &filePath) const
{
    QSqlQuery query(dbsqlite);
    query.prepare("SELECT COUNT(*) FROM FilePaths WHERE file_path = :filePath");
    query.bindValue(":filePath", filePath);

    if (!query.exec()) {
        qDebug() << "Database query error:" << query.lastError().text();
        return false;
    }

    if (query.next())
        return query.value(0).toInt() > 0;
    return false;
}

QStringList DBSQlite::getAllFilePaths() {
    QStringList filePaths;
    if (!open())
        qDebug() << "数据库连接初始化失败";
    QSqlQuery query(dbsqlite);  // 使用数据库连接执行查询
    if (!query.exec("SELECT file_path FROM FilePaths")) {
        qDebug() << "查询失败：" << query.lastError().text();
        return filePaths;
    }

    while (query.next())
        filePaths.append(query.value(0).toString());
    return filePaths;
}

QStringList DBSQlite::getAllTags() {
    QStringList tags;
    QSqlQuery query(dbsqlite);

    if (query.exec("SELECT DISTINCT tag_name FROM Tags")) {
        while (query.next()) {
            tags << query.value(0).toString();
        }
    }
    return tags;

}

void DBSQlite::saveExpirationDate(int fileId, const QDateTime &expirationDateTime) {
    QSqlQuery query(dbsqlite);

    query.prepare("UPDATE FilePaths SET expiration_date = :expiration_date WHERE id = :file_id");
    query.bindValue(":expiration_date", expirationDateTime);
    query.bindValue(":file_id", fileId);
    query.exec();
}

QList<FilePathInfo> DBSQlite::getFilePathsByTag(const QString &tag) {
    QList<FilePathInfo> filePathsWithTags;
        QSqlQuery query(dbsqlite);


    if (tag == "刷新") {
        query.prepare("SELECT fp.file_path, t.tag_name, fp.expiration_date FROM FilePaths fp JOIN Tags t ON fp.id = t.file_id");
    } else {
        query.prepare("SELECT fp.file_path, t.tag_name, fp.expiration_date FROM FilePaths fp JOIN Tags t ON fp.id = t.file_id WHERE t.tag_name = :tag");
        query.bindValue(":tag", tag);
    }

    query.exec();

    while (query.next()) {
        FilePathInfo info;
        info.filePath = query.value(0).toString();
        info.tagName = query.value(1).toString();
        info.expirationDate = query.value(2).toDateTime();

        filePathsWithTags.append(info);
    }

    return filePathsWithTags;
}


QStringList DBSQlite::searchFiles(const QString &keyword) {
    QStringList filePaths;
        QSqlQuery query(dbsqlite);

    query.prepare("SELECT DISTINCT file_path FROM FilePaths fp "
                  "LEFT JOIN Tags t ON fp.id = t.file_id "
                  "WHERE file_path LIKE :keyword OR t.tag_name LIKE :keyword");
    query.bindValue(":keyword", "%" + keyword + "%");
    query.exec();

    while (query.next()) {
        filePaths << query.value(0).toString();
    }
    return filePaths;
}


QVector<QPair<QString, QDateTime>> DBSQlite::getSortByExp() {
    QVector<QPair<QString, QDateTime>> fileList;
        QSqlQuery query(dbsqlite);


    // 执行查询，按到期时间排序
    query.prepare("SELECT file_path, expiration_date FROM FilePaths ORDER BY expiration_date ASC");
    query.exec();

    while (query.next()) {
        QString filePath = query.value(0).toString();
        QDateTime expirationDateTime = query.value(1).toDateTime();
        fileList.append(qMakePair(filePath, expirationDateTime));
    }
    return fileList;
}
