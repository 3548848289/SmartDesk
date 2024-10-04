#include "DBMySQL.h"

DBMySQL::DBMySQL() {
    dbmysql = QSqlDatabase::addDatabase("QMYSQL");
    //    dbmysql.setHostName("192.168.240.236");
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

    // 创建 users 表，包含用户登录密码和共享口令字段
    QString createUsersTableQuery = R"(
        CREATE TABLE IF NOT EXISTS users (
            username VARCHAR(10) PRIMARY KEY,
            password VARCHAR(255) NOT NULL,
            share_token VARCHAR(255) NOT NULL UNIQUE,
            avatar BLOB
        );
    )";

    if (!query.exec(createUsersTableQuery)) {
        qDebug() << "Failed to create 'users' table: " << query.lastError().text();
        return false;
    }

    // 创建 user_info 表，用于存储用户的其他个人信息
    QString createUserInfoTableQuery = R"(
        CREATE TABLE IF NOT EXISTS user_info (
            id INT AUTO_INCREMENT PRIMARY KEY,
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

    if (!query.exec(createUserInfoTableQuery)) {
        qDebug() << "Failed to create 'user_info' table: " << query.lastError().text();
        return false;
    }

    // 创建 SharedFiles 表，通过 share_token 关联到用户
    QString createSharedFilesTableSQL = R"(
        CREATE TABLE IF NOT EXISTS SharedFiles (
            id INT AUTO_INCREMENT PRIMARY KEY,
            local_file_path VARCHAR(255) NOT NULL,
            remote_file_name VARCHAR(255) NOT NULL,
            share_token VARCHAR(255) NOT NULL,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (share_token) REFERENCES users(share_token) ON DELETE CASCADE
        );
    )";

    if (!query.exec(createSharedFilesTableSQL)) {
        qDebug() << "Error creating tables:" << query.lastError();
        return false;
    }

    return true;
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
