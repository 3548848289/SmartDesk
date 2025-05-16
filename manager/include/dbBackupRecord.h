#ifndef DBBACKUPRECORD_H
#define DBBACKUPRECORD_H

#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QDateTime>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "dbManager.h"

class dbBackupRecord : public dbManager {

public:
    dbBackupRecord(const QString &dbName);  // 构造函数声明
    ~dbBackupRecord();

    void recordSubmission(const QString &filePath, const QString &backupFilePath);
    QList<QString> getRecordSub(const QString& filePath);
    bool hasSubmissions(const QString& filePath) const;


    bool insertSharedFile(const QString &filePath, const QString &fileName, const QString &shareToken);
    int getPasswordIdByPassword(const QString &password);


    QString getInitPath(const QString &remoteFileName);
    QDateTime getSubTime(const QString &remoteFileName);

    QList<QString> getAllFileNames();
    QList<QString> getBackupFileNames(const QString &filePath);
    bool deleteBackupRecord(const QString &filePath);
    bool updateFilePath(const QString &oldFilePath, const QString &newFilePath);
    bool updateSubmissions(const QString &oldFilePath, const QString &newFilePath);
    bool deleteAll(const QString &filePath);
    QList<QString> getBackupFileList(const QString &filePath);
};

#endif // DBBACKUPRECORD_H
