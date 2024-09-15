// DatabaseManager.cpp
#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(const QString &dbName) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
}

DatabaseManager::~DatabaseManager() {
    close();
}

bool DatabaseManager::open() {
    if (!db.open()) {
        qDebug() << "数据库连接失败：" << db.lastError().text();
                                          return false;
    }
    initializeDatabase();
    return true;
}

void DatabaseManager::close() {
    if (db.isOpen()) {
        db.close();
    }
}

void DatabaseManager::initializeDatabase() {
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS FilePaths (id INTEGER PRIMARY KEY, file_path TEXT UNIQUE)");
    query.exec("CREATE TABLE IF NOT EXISTS Tags (id INTEGER PRIMARY KEY, file_id INTEGER, tag_name TEXT, FOREIGN KEY(file_id) REFERENCES FilePaths(id))");
    query.exec("CREATE TABLE IF NOT EXISTS Annotations (id INTEGER PRIMARY KEY, file_id INTEGER, annotation TEXT, FOREIGN KEY(file_id) REFERENCES FilePaths(id))");
}

bool DatabaseManager::addFilePath(const QString &filePath, int &fileId) {
    QSqlQuery query;
    query.prepare("INSERT INTO FilePaths (file_path) VALUES (:filePath)");
    query.bindValue(":filePath", filePath);

    if (!query.exec()) {
        qDebug() << "插入文件路径失败：" << query.lastError().text();
                                            return false;
    }
    fileId = query.lastInsertId().toInt();
    return true;
}

bool DatabaseManager::getFileId(const QString &filePath, int &fileId) {
    QSqlQuery query;
    query.prepare("SELECT id FROM FilePaths WHERE file_path = :filePath");
    query.bindValue(":filePath", filePath);

    if (query.exec() && query.next()) {
        fileId = query.value(0).toInt();
        return true;
    }
    return false;
}

bool DatabaseManager::getTags(int fileId, QStringList &tags) {
    QSqlQuery query;
    query.prepare("SELECT tag_name FROM Tags WHERE file_id = :fileId");
    query.bindValue(":fileId", fileId);

    if (query.exec()) {
        while (query.next()) {
            tags.append(query.value(0).toString());
        }
        return true;
    }
    return false;
}

bool DatabaseManager::getAnnotation(int fileId, QString &annotation) {
    QSqlQuery query;
    query.prepare("SELECT annotation FROM Annotations WHERE file_id = :fileId");
    query.bindValue(":fileId", fileId);

    if (query.exec() && query.next()) {
        annotation = query.value(0).toString();
        return true;
    }
    return false;
}

bool DatabaseManager::saveTags(int fileId, const QStringList &tags) {
    QSqlQuery query;
    query.prepare("DELETE FROM Tags WHERE file_id = :fileId");
    query.bindValue(":fileId", fileId);
    query.exec();

    for (const QString &tag : tags) {
        query.prepare("INSERT INTO Tags (file_id, tag_name) VALUES (:fileId, :tagName)");
        query.bindValue(":fileId", fileId);
        query.bindValue(":tagName", tag);
        query.exec();
    }
    return true;
}

bool DatabaseManager::saveAnnotation(int fileId, const QString &annotation) {
    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO Annotations (file_id, annotation) VALUES (:fileId, :annotation)");
    query.bindValue(":fileId", fileId);
    query.bindValue(":annotation", annotation);
    return query.exec();
}

bool DatabaseManager::hasTagsForFile(const QString &filePath) const
{
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM FilePaths WHERE file_path = :filePath");
    query.bindValue(":filePath", filePath);

    if (!query.exec()) {
        qDebug() << "Database query error:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        return query.value(0).toInt() > 0;
    }

    return false;
}
