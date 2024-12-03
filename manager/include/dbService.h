#ifndef DBSERVICE_H
#define DBSERVICE_H

#include "dbFilepath.h"
#include "dbBackupRecord.h"
#include <QString>

class dbService {
public:
    // 获取单例实例
    static dbService& instance(const QString &dbName = "default.db") {
        static dbService instance(dbName);  // 使用静态局部变量实现单例
        return instance;
    }

    // 删除拷贝构造函数和赋值运算符，确保单例的唯一性
    dbService(const dbService&) = delete;
    dbService& operator=(const dbService&) = delete;

    // 提供对 dbFilepath 和 dbBackupRecord 的访问接口
    dbFilepath& dbTags() { return dbfilepath; }
    dbBackupRecord& dbBackup() { return dbbackuprecord; }

    // AnnotationManager 和 ExpirationManager 可以根据需要启用
    // AnnotationManager& annotationManager() { return annotationMgr; }
    // ExpirationManager& expirationManager() { return expirationMgr; }

private:
    // 构造函数私有化，确保只能通过 instance() 获取实例
    dbService(const QString &dbName)
        : dbfilepath(dbName), dbbackuprecord(dbName) {
    }

    // 成员变量：数据库管理器
    dbFilepath dbfilepath;
    dbBackupRecord dbbackuprecord;
    // AnnotationManager annotationMgr;
    // ExpirationManager expirationMgr;
};

#endif // DBSERVICE_H
