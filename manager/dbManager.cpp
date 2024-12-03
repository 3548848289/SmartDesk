#include "dbManager.h"

dbManager::dbManager(const QString &dbName)
{
    QString connectionName = "sqlite_" + QUuid::createUuid().toString();
    dbsqlite = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    dbsqlite.setDatabaseName(dbName);

    if (!dbsqlite.open()) {
        qDebug() << "数据库连接初始化失败:" << dbsqlite.lastError().text();
    }
    else
        initializeTables();
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

bool dbManager::initializeTables() {
    QSqlQuery query(dbsqlite);

    // 启动事务
    if (!dbsqlite.transaction()) {
        qDebug() << "Failed to start transaction: " << dbsqlite.lastError().text();
        return false;
    }

    // 定义所有的表创建 SQL 语句及其表名
    QList<QPair<QString, QString>> tables = {
        {"Submissions", R"(
            CREATE TABLE IF NOT EXISTS Submissions (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                file_path TEXT NOT NULL,
                submit_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            );
        )"},
        {"SubmissionRecords", R"(
            CREATE TABLE IF NOT EXISTS SubmissionRecords (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                submission_id INTEGER,
                submit_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                FOREIGN KEY (submission_id) REFERENCES Submissions(id) ON DELETE CASCADE
            );
        )"},
        {"SharedFiles", R"(
            CREATE TABLE IF NOT EXISTS SharedFiles (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                local_file_path TEXT NOT NULL,
                remote_file_name TEXT NOT NULL,
                share_token TEXT NOT NULL,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                FOREIGN KEY (share_token) REFERENCES users(share_token) ON DELETE CASCADE
            );
        )"},
        {"FilePaths", R"(
            CREATE TABLE IF NOT EXISTS FilePaths (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                file_path TEXT UNIQUE NOT NULL,
                expiration_date DATE
            );
        )"},
        {"Tags", R"(
            CREATE TABLE IF NOT EXISTS Tags (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                file_id INTEGER NOT NULL,
                tag_name TEXT NOT NULL,
                FOREIGN KEY(file_id) REFERENCES FilePaths(id) ON DELETE CASCADE
            );
        )"},
        {"Annotations", R"(
            CREATE TABLE IF NOT EXISTS Annotations (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                file_id INTEGER NOT NULL,
                annotation TEXT NOT NULL,
                FOREIGN KEY(file_id) REFERENCES FilePaths(id) ON DELETE CASCADE
            );
        )"}
    };

    for (const auto& table : tables) {
        const QString& tableName = table.first;
        const QString& createTableSQL = table.second;

        if (!query.exec(createTableSQL)) {
            qDebug() << "Failed to create '" << tableName << "' table: " << query.lastError().text();
            dbsqlite.rollback();
            return false;
        }
    }

    // 提交事务
    if (!dbsqlite.commit()) {
        qDebug() << "Failed to commit transaction: " << dbsqlite.lastError().text();
        dbsqlite.rollback();  // 回滚事务
        return false;
    }

    return true;
}
