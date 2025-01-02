#ifndef DBSERVICE_H
#define DBSERVICE_H

#include "dbFilepath.h"
#include "dbBackupRecord.h"
#include "dbOnlineDoc.h"
#include <QString>

class dbService {
public:
    static dbService& instance(const QString &dbName = "default.db") {
        static dbService instance(dbName);
        return instance;
    }

    dbService(const dbService&) = delete;
    dbService& operator=(const dbService&) = delete;

    dbFilepath& dbTags() { return dbfilepath; }
    dbBackupRecord& dbBackup() { return dbbackuprecord; }
    dbOnlineDoc& dbOnline() { return dbonline; }

private:
    dbService(const QString &dbName)
        : dbfilepath(dbName), dbbackuprecord(dbName), dbonline(dbName) {
    }

    dbFilepath dbfilepath;
    dbBackupRecord dbbackuprecord;
    dbOnlineDoc dbonline;
    QString currentDbName;
};

#endif // DBSERVICE_H
