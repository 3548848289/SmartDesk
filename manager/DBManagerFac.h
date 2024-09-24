#ifndef DBMANAGERFAC_H
#define DBMANAGERFAC_H

#include "DBMySQL.h"
#include "DBSQlite.h"

class DBManagerFac {
public:
    virtual DatabaseManager* createDatabaseManager() = 0;
    virtual MySQLManager* createMySQLManager() = 0;
    virtual ~DatabaseManagerFactory() {}
};

#endif // DBMANAGERFAC_H




// SQLiteStorageFactory.h
#ifndef SQLITESTORAGEFACTORY_H
#define SQLITESTORAGEFACTORY_H

class SQLiteStorageFactory : public DBManagerFac {
public:
    DatabaseManager* createDatabaseManager() override {
        return new DatabaseManager("file_metadata.db");
    }

    MySQLManager* createMySQLManager() override {
        // 这里可以返回 nullptr 或实现一个特定的 MySQL 管理类
        return nullptr; // 或者你可以根据需要实现
    }
};

#endif // SQLITESTORAGEFACTORY_H

// MySQLStorageFactory.h
#ifndef MYSQLSTORAGEFACTORY_H
#define MYSQLSTORAGEFACTORY_H

class MySQLStorageFactory : public DBManagerFac {
public:
    DatabaseManager* createDatabaseManager() override {
        // 可以返回 nullptr 或实现一个特定的 DatabaseManager
        return nullptr; // 或者你可以根据需要实现
    }

    MySQLManager* createMySQLManager() override {
        return new MySQLManager("your_mysql_database_name");
    }
};

#endif // MYSQLSTORAGEFACTORY_H
