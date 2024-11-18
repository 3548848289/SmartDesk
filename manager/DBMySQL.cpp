#include "DBMySQL.h"

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

    qDebug() << "All tables created successfully.";
    return true;
}

void DBMySQL::recordSubmission(const QString &filePath) {
    QSqlQuery query(dbmysql);
    query.prepare("SELECT id FROM Submissions WHERE file_path = :filePath");
    query.bindValue(":filePath", filePath);

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
        return;
    }

    int submissionId;
    if (query.next()) {
        submissionId = query.value(0).toInt();
        qDebug() << "Existing submission found with ID:" << submissionId;
    } else {
        // 如果没有记录，则插入新记录到 Submissions 表
        query.prepare("INSERT INTO Submissions (file_path) VALUES (:filePath)");
        query.bindValue(":filePath", filePath);

        if (!query.exec()) {
            qDebug() << "Insert into Submissions failed:" << query.lastError();
            return;
        }

        submissionId = query.lastInsertId().toInt();
        qDebug() << "New submission recorded with ID:" << submissionId;
    }

    // 获取原始文件名（例如：DCommit.cpp）
    QString baseFileName = QFileInfo(filePath).baseName();  // 例如 "DCommit"
    QString fileExtension = QFileInfo(filePath).completeSuffix();  // 例如 "cpp"

    // 查询已有的提交记录数
    QSqlQuery countQuery(dbmysql);
    countQuery.prepare("SELECT COUNT(*) FROM SubmissionRecords WHERE submission_id = :submissionId");
    countQuery.bindValue(":submissionId", submissionId);

    if (!countQuery.exec()) {
        qDebug() << "Count query failed:" << countQuery.lastError();
        return;
    }

    int submissionCount = 0;
    if (countQuery.next()) {
        submissionCount = countQuery.value(0).toInt();
    }

    // 基于提交次数生成新的文件名
    int newSubmissionNumber = submissionCount + 1;
    QString remoteFileName = QString("%1%2.%3").arg(baseFileName).arg(newSubmissionNumber).arg(fileExtension);

    qDebug() << "New remote file name:" << remoteFileName;

    // 插入新的记录到 SubmissionRecords 表
    QSqlQuery recordQuery(dbmysql);
    recordQuery.prepare("INSERT INTO SubmissionRecords (submission_id, remote_file_name) VALUES (:submissionId, :remoteFileName)");
    recordQuery.bindValue(":submissionId", submissionId);
    recordQuery.bindValue(":remoteFileName", remoteFileName);

    if (!recordQuery.exec()) {
        qDebug() << "Insert into SubmissionRecords failed:" << recordQuery.lastError();
    } else {
        qDebug() << "Record added for submission ID:" << submissionId << " with remote file name:" << remoteFileName;
    }
}


bool DBMySQL::hasSubmissions(const QString& filePath) const {
    QSqlQuery query(dbmysql);
    query.prepare("SELECT COUNT(*) FROM Submissions WHERE file_path = :filePath");
    query.bindValue(":filePath", filePath);

    if (!query.exec()) {
//        qDebug() << "DBMySQL::hasSubmissions Query failed:" << query.lastError();
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

bool DBMySQL::loginUser(const QString &username, const QString &password, QByteArray &avatarData, QString &statusMessage) {
        QSqlQuery query(dbmysql);

    query.prepare("SELECT password, avatar FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (query.exec()) {
        if (query.next()) {
            QString dbPassword = query.value(0).toString();
            avatarData = query.value(1).toByteArray();

            if (dbPassword == password) {
                statusMessage = "登录成功";
                return true;
            } else {
                statusMessage = "密码错误";
                return false;
            }
        } else {
            statusMessage = "用户不存在";
            return false;
        }
    } else {
        statusMessage = "数据库查询失败: " + query.lastError().text();
                                                    return false;
    }
}


QString generateShareToken(const QString &password) {

    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);

    QString hexHash = hash.toHex();

    QString shareToken = hexHash.left(6);
    return shareToken;
}

bool DBMySQL::registerUser(const QString &username, const QString &password, const QByteArray &avatarData, QString &statusMessage) {
    QSqlQuery query(dbmysql);

    // 直接存储用户输入的原始密码
    QString shareToken = generateShareToken(password);  // 根据密码生成共享口令

    // 准备插入语句
    query.prepare("INSERT INTO users (username, password, avatar, share_token) VALUES (:username, :password, :avatar, :share_token)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);  // 直接存储原始密码
    query.bindValue(":avatar", avatarData);
    query.bindValue(":share_token", shareToken);  // 插入生成的共享口令

    // 执行插入操作
    if (query.exec()) {
                                                    statusMessage = "注册成功";
                                                    return true;
    } else {
                                                    qDebug() << "注册失败: " << query.lastError().text();
                                                                                    statusMessage = "注册失败: " + query.lastError().text();
                                                                             return false;
    }
}


QString DBMySQL::lastError() const {
    return dbmysql.lastError().text();
}

QMap<QString, QVariant> DBMySQL::getUserInfo(const QString& username) {
    QMap<QString, QVariant> userInfo;
        QSqlQuery query(dbmysql);


    // 使用JOIN查询用户信息和头像
    query.prepare(R"(
        SELECT u.username, u.avatar, ui.name, ui.motto, ui.gender, ui.birthday, ui.location, ui.company
        FROM users u
        JOIN user_info ui ON u.username = ui.username
        WHERE u.username = :username
    )");
    query.bindValue(":username", username);

    qDebug() << "Fetching user info for username:" << username;

    if (query.exec()) {
                                           if (query.next()) {
            qDebug() << "User found:" << query.value("username").toString();
            userInfo["username"] = query.value("username").toString();
            userInfo["avatar"] = query.value("avatar").toByteArray();
            userInfo["name"] = query.value("name").toString();
            userInfo["motto"] = query.value("motto").toString();
            userInfo["gender"] = query.value("gender").toString();
            userInfo["birthday"] = query.value("birthday").toDate();
            userInfo["location"] = query.value("location").toString();
            userInfo["company"] = query.value("company").toString();
                                           } else {
            qDebug() << "No user found for username:" << username;
                                           }
    } else {
                                           qDebug() << "Query execution failed:" << query.lastError().text();
    }

    return userInfo;    
}

bool DBMySQL::insertUserInfo(const QString& username, const QMap<QString, QVariant>& userInfo) {
        QSqlQuery query(dbmysql);

    query.prepare("INSERT INTO user_info (username, name, motto, gender, birthday, location, company) "
                  "VALUES (:username, :name, :motto, :gender, :birthday, :location, :company)");

    query.bindValue(":username", username);
    query.bindValue(":name", userInfo["name"]);
    query.bindValue(":motto", userInfo["motto"]);
    query.bindValue(":gender", userInfo["gender"]);
    query.bindValue(":birthday", userInfo["birthday"]);
    query.bindValue(":location", userInfo["location"]);
    query.bindValue(":company", userInfo["company"]);

    if (!query.exec()) {
        qDebug() << "DBMySQL::insertUserInfo Failed to insert user info:" << query.lastError().text();
        return false;
    }
    qDebug() << "User info inserted successfully for username:" << username;
    return true;
}


bool DBMySQL::updateUserInfo(const QString& username, const QMap<QString, QVariant>& userInfo) {
        QSqlQuery query(dbmysql);

    query.prepare("UPDATE user_info SET name = :name, motto = :motto, gender = :gender, "
                  "birthday = :birthday, location = :location, company = :company "
                  "WHERE username = :username");

    query.bindValue(":name", userInfo["name"]);
    query.bindValue(":motto", userInfo["motto"]);
    query.bindValue(":gender", userInfo["gender"]);
    query.bindValue(":birthday", userInfo["birthday"]);
    query.bindValue(":location", userInfo["location"]);
    query.bindValue(":company", userInfo["company"]);
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "DBMySQL::updateUserInfo Failed to update user info:" << query.lastError().text();
        return false;
    }
    qDebug() << "DBMySQL::updateUserInfo User info updated successfully for username:" << username;
    return true;
}
