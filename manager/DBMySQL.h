#ifndef DBMYSQL_H
#define DBMYSQL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QVariant>
#include <QDate>
#include <QMap>
#include <QDebug>
#include <QMessageBox>

class DBMySQL {
public:
    static DBMySQL& instance() {
        static DBMySQL instance; // 懒汉式单例
        return instance;
    }

    bool open();
    void close();
    bool createTable();

    bool loginUser(const QString &username, const QString &password, QByteArray &avatarData, QString &statusMessage);
    bool registerUser(const QString &username, const QString &password, const QByteArray &avatarData, QString &statusMessage);

    QString lastError() const;

    QMap<QString, QVariant> getUserInfo(const QString& username);

    bool insertUserInfo(const QString& username, const QMap<QString, QVariant>& userInfo);
    bool updateUserInfo(const QString& username, const QMap<QString, QVariant>& userInfo);

private:
    DBMySQL(); // 构造函数私有
    ~DBMySQL(); // 析构函数私有
    DBMySQL(const DBMySQL&) = delete; // 禁用复制构造函数
    DBMySQL& operator=(const DBMySQL&) = delete; // 禁用赋值运算符

    QSqlDatabase dbmysql;
};

#endif // DBMYSQL_H
