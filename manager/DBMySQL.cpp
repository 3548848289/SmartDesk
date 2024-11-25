#include "include/DBMySQL.h"

DBMySQL::DBMySQL() {
    dbmysql = QSqlDatabase::addDatabase("QMYSQL");
    dbmysql.setHostName("127.0.0.1");
    dbmysql.setDatabaseName("mytxt");
    dbmysql.setUserName("root");
    dbmysql.setPassword("Mysql20039248");
    if (!dbmysql.open()) {
        qDebug() << "无法连接到数据库:" << dbmysql.lastError().text();
        return;
    }
    if (!createTable()) {
        qDebug() << "创建表失败: " << lastError();
    }

}

DBMySQL::~DBMySQL() {
    if (dbmysql.isOpen()) {
        QSqlQuery().finish();
        dbmysql.close();
    }
    QSqlDatabase::removeDatabase(dbmysql.connectionName());

}

bool DBMySQL::createTable() {
    QSqlQuery query(dbmysql);

    // 启动事务
    if (!dbmysql.transaction()) {
        qDebug() << "Failed to start transaction: " << dbmysql.lastError().text();
        return false;
    }

    // 创建 Submissions 表
    QString createSubmissionsTableSQL = R"(
        CREATE TABLE IF NOT EXISTS Submissions (
            id INT PRIMARY KEY AUTO_INCREMENT,
            file_path TEXT NOT NULL,
            submit_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        );
    )";
    if (!query.exec(createSubmissionsTableSQL)) {
        qDebug() << "Failed to create 'Submissions' table: " << query.lastError().text();
        dbmysql.rollback();  // 回滚事务
        return false;
    }

    // 创建 SubmissionRecords 表
    QString createSubmissionRecordsTableSQL = R"(
        CREATE TABLE IF NOT EXISTS SubmissionRecords (
            id INT PRIMARY KEY AUTO_INCREMENT,
            submission_id INT,
            submit_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (submission_id) REFERENCES Submissions(id) ON DELETE CASCADE
        );
    )";
    if (!query.exec(createSubmissionRecordsTableSQL)) {
        qDebug() << "Failed to create 'SubmissionRecords' table: " << query.lastError().text();
        dbmysql.rollback();  // 回滚事务
        return false;
    }

    // 创建 users 表
    QString createUsersTableSQL = R"(
        CREATE TABLE IF NOT EXISTS users (
            username VARCHAR(10) PRIMARY KEY,
            password VARCHAR(255) NOT NULL,
            share_token VARCHAR(255) NOT NULL UNIQUE,
            avatar BLOB
        );
    )";
    if (!query.exec(createUsersTableSQL)) {
        qDebug() << "Failed to create 'users' table: " << query.lastError().text();
        dbmysql.rollback();  // 回滚事务
        return false;
    }

    // 创建 user_info 表
    QString createUserInfoTableSQL = R"(
        CREATE TABLE IF NOT EXISTS user_info (
            id INT PRIMARY KEY AUTO_INCREMENT,
            username VARCHAR(10),
            name VARCHAR(20),
            motto VARCHAR(50),
            gender ENUM('Male', 'Female', 'Other'),
            birthday DATE,
            location VARCHAR(100),
            company VARCHAR(100),
            FOREIGN KEY (username) REFERENCES users(username) ON DELETE CASCADE
        );
    )";
    if (!query.exec(createUserInfoTableSQL)) {
        qDebug() << "Failed to create 'user_info' table: " << query.lastError().text();
        dbmysql.rollback();  // 回滚事务
        return false;
    }

    // 创建 SharedFiles 表
    QString createSharedFilesTableSQL = R"(
        CREATE TABLE IF NOT EXISTS SharedFiles (
            id INT PRIMARY KEY AUTO_INCREMENT,
            local_file_path VARCHAR(255) NOT NULL,
            remote_file_name VARCHAR(255) NOT NULL,
            share_token VARCHAR(255) NOT NULL,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (share_token) REFERENCES users(share_token) ON DELETE CASCADE
        );
    )";
    if (!query.exec(createSharedFilesTableSQL)) {
        qDebug() << "Failed to create 'SharedFiles' table: " << query.lastError().text();
        dbmysql.rollback();  // 回滚事务
        return false;
    }

    // 提交事务
    if (!dbmysql.commit()) {
        qDebug() << "Failed to commit transaction: " << dbmysql.lastError().text();
        dbmysql.rollback();  // 回滚事务
        return false;
    }
    return true;
}

void DBMySQL::recordSubmission(const QString &filePath, const QString &backupFilePath) {
    QSqlQuery query(dbmysql);
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    query.prepare("SELECT id FROM submission WHERE file_path = :filePath");
    query.bindValue(":filePath", filePath);
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
        return;
    }

    int submissionId = -1;
    if (query.next()) {
        submissionId = query.value(0).toInt();     // 如果已有记录，获取ID
    } else {
        // 没有记录，插入新记录并获取 ID
        query.prepare("INSERT INTO submission (file_path, submit_time) VALUES (:filePath, :submitTime)");
        query.bindValue(":filePath", filePath);
        query.bindValue(":submitTime", currentTime);

        if (!query.exec()) {
            qDebug() << "Insert into submission failed:" << query.lastError();
            return;
        }
        submissionId = query.lastInsertId().toInt();
    }

    // 插入记录到 submissionrecord 表
    query.prepare("INSERT INTO submissionrecord (submission_id, remote_file_name, submit_time) "
                  "VALUES (:submissionId, :backupFilePath, :submitTime)");
    query.bindValue(":submissionId", submissionId);
    query.bindValue(":backupFilePath", backupFilePath);
    query.bindValue(":submitTime", currentTime);

    if (!query.exec()) {
        qDebug() << "Insert into submissionrecord failed:" << query.lastError();
    } else {
        qDebug() << "Record added for submission ID:" << submissionId << " with remote file name:" << backupFilePath;
    }
}



QList<QString> DBMySQL::getRecordSub(const QString& filePath) {
    QSqlQuery query(dbmysql);

    query.prepare("SELECT sr.remote_file_name "
                  "FROM submissionrecord sr "
                  "JOIN submission s ON sr.submission_id = s.id "
                  "WHERE s.file_path = :filePath");

    query.bindValue(":filePath", filePath);

    QList<QString> filePaths;
    if (query.exec()) {
        while (query.next()) {
            QString remoteFilePath = query.value(0).toString();
            filePaths.append(remoteFilePath);
        }
        for (const QString &path : filePaths) {
            qDebug() << "File Path: " << path;
        }
    } else {
        qDebug() << "Query failed: " << query.lastError().text();
    }
    return filePaths;
}

bool DBMySQL::hasSubmissions(const QString& filePath) const {
    QSqlQuery query(dbmysql);
    query.prepare("SELECT COUNT(*) FROM submission WHERE file_path = :filePath");
    query.bindValue(":filePath", filePath);

    if (!query.exec()) {
        qDebug() << "DBMySQL::hasSubmissions Query failed:" << query.lastError();
        return false;
    }
    if (query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}



bool DBMySQL::insertSharedFile(const QString &filePath, const QString &fileName, const QString &shareToken) {
    QSqlQuery query(dbmysql);

    // 准备 INSERT 语句，并包含 share_token
    query.prepare("INSERT INTO SharedFiles (local_file_path, remote_file_name, share_token) "
                  "VALUES (:local_file_path, :remote_file_name, :share_token)");
    query.bindValue(":local_file_path", filePath);
    query.bindValue(":remote_file_name", fileName);
    query.bindValue(":share_token", shareToken);  // 确保绑定了 share_token 的值

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "插入共享文件失败: " << query.lastError().text();
                                                    return false;
    }
}



int DBMySQL::getPasswordIdByPassword(const QString &password) {
    QSqlQuery query(dbmysql);

    query.prepare("SELECT id FROM users WHERE password = :password");
    query.bindValue(":password", password);  // 绑定用户提供的口令

    if (query.exec() && query.next()) {
        return query.value(0).toInt();  // 返回匹配的 passwordId
    } else {
        qDebug() << "Failed to retrieve password ID: " << query.lastError().text();
        return -1;  // 如果查询失败，返回 -1
    }
}

QStringList DBMySQL::getSharedFilesByShareToken(const QString &shareToken) {
    QSqlQuery query(dbmysql);

    query.prepare(R"(
        SELECT remote_file_name, local_file_path
        FROM SharedFiles
        WHERE share_token = :share_token
    )");
    query.bindValue(":share_token", shareToken);
    qDebug() << shareToken;

    QStringList fileList;

    if (query.exec()) {
        while (query.next()) {
            QString remoteFileName = query.value(0).toString();  // 远程文件名
            QString localFilePath = query.value(1).toString();   // 本地文件路径
            fileList.append(remoteFileName + " " + localFilePath);  // 用空格分隔文件名和路径
        }
    } else {
        qDebug() << "Failed to retrieve shared files: " << query.lastError().text();
    }

    return fileList;
}



bool DBMySQL::open() {
    return dbmysql.open();
}


QString DBMySQL::lastError() const {
    return dbmysql.lastError().text();
}
