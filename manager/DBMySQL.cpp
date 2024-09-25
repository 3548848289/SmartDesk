#include "DBMySQL.h"



DBMySQL::DBMySQL()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("mytxt");
    db.setUserName("root");
    db.setPassword("Mysql20039248");
    if (!db.open()) {
        qDebug() << "无法连接到数据库";
        return;
    }

    if (!createTable()) {
        qDebug() << "创建表失败: " << lastError();
    }
}

DBMySQL::~DBMySQL() {
    db.close();
}

bool DBMySQL::createTable() {
    QSqlQuery query;

    QString createUsersTableQuery = R"(
        CREATE TABLE IF NOT EXISTS users (
            username VARCHAR(10) PRIMARY KEY,
            password VARCHAR(15) NOT NULL,
            avatar BLOB
            );
    )";

    if (!query.exec(createUsersTableQuery)) {
        qDebug() << "Failed to create 'users' table: " << query.lastError().text();
        return false;
    }

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

    qDebug() << "Table 'user_info' created successfully!";
    return true;
}


bool DBMySQL::open() {
    return db.open();
}

bool DBMySQL::loginUser(const QString &username, const QString &password, QByteArray &avatarData, QString &statusMessage) {
    QSqlQuery query;
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

bool DBMySQL::registerUser(const QString &username, const QString &password, const QByteArray &avatarData, QString &statusMessage) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password, avatar) VALUES (:username, :password, :avatar)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":avatar", avatarData);

    if (query.exec()) {
        statusMessage = "注册成功";
        return true;
    } else {
        qDebug() << query.lastError().text();
        statusMessage = "注册失败: " + query.lastError().text();
                                           return false;
    }
}

QString DBMySQL::lastError() const {
    return db.lastError().text();
}

QMap<QString, QVariant> DBMySQL::getUserInfo(const QString& username) {
    QMap<QString, QVariant> userInfo;
    QSqlQuery query;

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
        userInfo["username"] = query.value("username").toString();
        userInfo["avatar"] = query.value("avatar").toByteArray();
        userInfo["name"] = query.value("name").toString();
        userInfo["motto"] = query.value("motto").toString();
        userInfo["gender"] = query.value("gender").toString();
        userInfo["birthday"] = query.value("birthday").toDate();
        userInfo["location"] = query.value("location").toString();
        userInfo["company"] = query.value("company").toString();
        } else {
            qDebug() << "DBMySQL::getUserInfo No user found with username:" << username;
        }
    } else {
        qDebug() << "DBMySQL::getUserInfo Failed to execute query:" << query.lastError().text();
    }

    return userInfo;
}



bool DBMySQL::insertUserInfo(const QString& username, const QMap<QString, QVariant>& userInfo) {
    QSqlQuery query;
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
    QSqlQuery query;
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
