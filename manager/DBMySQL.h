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
    DBMySQL();
    ~DBMySQL();

    bool createTable();

    bool open();
    bool loginUser(const QString &username, const QString &password, QByteArray &avatarData, QString &statusMessage);
    bool registerUser(const QString &username, const QString &password, const QByteArray &avatarData, QString &statusMessage);

    QString lastError() const;


    QMap<QString, QVariant> getUserInfo(const QString& username);

    bool insertUserInfo(const QString& username, const QMap<QString, QVariant>& userInfo);
    bool updateUserInfo(const QString& username, const QMap<QString, QVariant>& userInfo);

private:
    QSqlDatabase dbmysql;
};

#endif // DBMYSQL_H
