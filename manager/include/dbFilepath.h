#ifndef DBFILEPATH_H
#define DBFILEPATH_H

#include <QString>
#include <QStringList>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "dbManager.h"

class dbFilepath : public dbManager {

public:
    dbFilepath(const QString &dbName);  // 构造函数声明
    ~dbFilepath();


    bool addFilePath(const QString &filePath, int &fileId);
    bool getFileId(const QString &filePath, int &fileId);
    QStringList getAllFilePaths();
    QStringList searchFiles(const QString &keyword);
};


#endif // DBFILEPATH_H
