// DatabaseManager.h
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include <QDebug>

class DatabaseManager {
public:
    DatabaseManager(const QString &dbName = "file_metadata.db");
    ~DatabaseManager();

    bool open();
    void close();

    bool addFilePath(const QString &filePath, int &fileId);
    bool getFileId(const QString &filePath, int &fileId);

    bool getTags(int fileId, QStringList &tags);
    bool getAnnotation(int fileId, QString &annotation);

    bool saveTags(int fileId, const QStringList &tags);
    bool saveAnnotation(int fileId, const QString &annotation);
    bool hasTagsForFile(const QString &filePath) const;

private:
    QSqlDatabase db;
    void initializeDatabase();
};

#endif // DATABASEMANAGER_H
