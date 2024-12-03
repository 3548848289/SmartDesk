#ifndef DBSERVICE_H
#define DBSERVICE_H

#include "dbFilepath.h"
#include "dbBackupRecord.h"

class dbService {
public:
    dbService(const QString &dbName): dbfilepath(dbName), dbbackuprecord(dbName)
    {

    }
    ~dbService()
    {

    }
    dbFilepath& filePathManager() { return dbfilepath; }
    dbBackupRecord& backupRecordManager() { return dbbackuprecord; }
    // AnnotationManager& annotationManager() { return annotationMgr; }
    // ExpirationManager& expirationManager() { return expirationMgr; }

private:
    dbFilepath dbfilepath;
    dbBackupRecord dbbackuprecord;
    // AnnotationManager annotationMgr;
    // ExpirationManager expirationMgr;
};



#endif // DBSERVICE_H
