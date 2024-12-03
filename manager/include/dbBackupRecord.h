#ifndef DBBACKUPRECORD_H
#define DBBACKUPRECORD_H

#include <QString>
#include <QStringList>
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
    QStringList getSharedFilesByShareToken(const QString &shareToken);
    int getPasswordIdByPassword(const QString &password);


};

#endif // DBBACKUPRECORD_H
