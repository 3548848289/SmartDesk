#include "dbManager.h"

dbManager::dbManager(const QString &dbName)
{
    QString connectionName = "sqlite_" + QUuid::createUuid().toString();
    dbsqlite = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    dbsqlite.setDatabaseName(dbName);

    if (!dbsqlite.open()) {
        qDebug() << "数据库连接初始化失败:" << dbsqlite.lastError().text();
    }
}

dbManager::~dbManager()
{
    if (dbsqlite.isOpen()) {
        dbsqlite.close();  // 确保在析构时关闭数据库连接
    }
}

bool dbManager::open()
{
    return dbsqlite.open();
}

void dbManager::close()
{
    dbsqlite.close();
}

QString dbManager::lastError() const
{
    return dbsqlite.lastError().text();
}

bool dbManager::createTables()
{
    QSqlQuery query(dbsqlite);

    // 启动事务
    if (!dbsqlite.transaction()) {
        qDebug() << "Failed to start transaction: " << dbsqlite.lastError().text();
        return false;
    }

    // 创建 Submissions 表
    QString createSubmissionsTableSQL = R"(
        CREATE TABLE IF NOT EXISTS Submissions (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            file_path TEXT NOT NULL,
            submit_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        );
    )";
    if (!query.exec(createSubmissionsTableSQL)) {
        qDebug() << "Failed to create 'Submissions' table: " << query.lastError().text();
        dbsqlite.rollback();  // 回滚事务
        return false;
    }

    // 创建 SubmissionRecords 表
    QString createSubmissionRecordsTableSQL = R"(
        CREATE TABLE IF NOT EXISTS SubmissionRecords (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            submission_id INTEGER,
            submit_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (submission_id) REFERENCES Submissions(id) ON DELETE CASCADE
        );
    )";
    if (!query.exec(createSubmissionRecordsTableSQL)) {
        qDebug() << "Failed to create 'SubmissionRecords' table: " << query.lastError().text();
        dbsqlite.rollback();  // 回滚事务
        return false;
    }

    // 创建 users 表
    QString createUsersTableSQL = R"(
        CREATE TABLE IF NOT EXISTS users (
            username TEXT PRIMARY KEY,
            password TEXT NOT NULL,
            share_token TEXT NOT NULL UNIQUE,
            avatar BLOB
        );
    )";
    if (!query.exec(createUsersTableSQL)) {
        qDebug() << "Failed to create 'users' table: " << query.lastError().text();
        dbsqlite.rollback();  // 回滚事务
        return false;
    }

    // 创建 user_info 表
    QString createUserInfoTableSQL = R"(
        CREATE TABLE IF NOT EXISTS user_info (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT,
            name TEXT,
            motto TEXT,
            gender TEXT CHECK(gender IN ('Male', 'Female', 'Other')),
            birthday DATE,
            location TEXT,
            company TEXT,
            FOREIGN KEY (username) REFERENCES users(username) ON DELETE CASCADE
        );
    )";
    if (!query.exec(createUserInfoTableSQL)) {
        qDebug() << "Failed to create 'user_info' table: " << query.lastError().text();
        dbsqlite.rollback();  // 回滚事务
        return false;
    }

    // 创建 SharedFiles 表
    QString createSharedFilesTableSQL = R"(
        CREATE TABLE IF NOT EXISTS SharedFiles (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            local_file_path TEXT NOT NULL,
            remote_file_name TEXT NOT NULL,
            share_token TEXT NOT NULL,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (share_token) REFERENCES users(share_token) ON DELETE CASCADE
        );
    )";
    if (!query.exec(createSharedFilesTableSQL)) {
        qDebug() << "Failed to create 'SharedFiles' table: " << query.lastError().text();
        dbsqlite.rollback();  // 回滚事务
        return false;
    }

    // 添加 FilePaths 表
    QString createFilePathsTableSQL = R"(
        CREATE TABLE IF NOT EXISTS FilePaths (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            file_path TEXT UNIQUE NOT NULL,
            expiration_date DATE
        );
    )";
    if (!query.exec(createFilePathsTableSQL)) {
        qDebug() << "Failed to create 'FilePaths' table: " << query.lastError().text();
        dbsqlite.rollback();  // 回滚事务
        return false;
    }

    // 添加 Tags 表
    QString createTagsTableSQL = R"(
        CREATE TABLE IF NOT EXISTS Tags (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            file_id INTEGER NOT NULL,
            tag_name TEXT NOT NULL,
            FOREIGN KEY(file_id) REFERENCES FilePaths(id) ON DELETE CASCADE
        );
    )";
    if (!query.exec(createTagsTableSQL)) {
        qDebug() << "Failed to create 'Tags' table: " << query.lastError().text();
        dbsqlite.rollback();  // 回滚事务
        return false;
    }

    // 添加 Annotations 表
    QString createAnnotationsTableSQL = R"(
        CREATE TABLE IF NOT EXISTS Annotations (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            file_id INTEGER NOT NULL,
            annotation TEXT NOT NULL,
            FOREIGN KEY(file_id) REFERENCES FilePaths(id) ON DELETE CASCADE
        );
    )";
    if (!query.exec(createAnnotationsTableSQL)) {
        qDebug() << "Failed to create 'Annotations' table: " << query.lastError().text();
        dbsqlite.rollback();  // 回滚事务
        return false;
    }

    // 提交事务
    if (!dbsqlite.commit()) {
        qDebug() << "Failed to commit transaction: " << dbsqlite.lastError().text();
        dbsqlite.rollback();  // 回滚事务
        return false;
    }

    return true;
}
