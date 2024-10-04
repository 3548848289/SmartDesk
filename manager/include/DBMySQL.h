#ifndef DBMYSQL_H
#define DBMYSQL_H



#include "D:\\QT6\\6.6.0\\mingw_64\include\\QtSql\\QSqlDatabase"
#include "D:\\QT6\\6.6.0\\mingw_64\include\\QtSql\\QSqlQuery"
#include "D:\\QT6\\6.6.0\\mingw_64\include\\QtSql\\QSqlError"
#include <QString>
#include <QVariant>
#include <QDate>
#include <QMap>
#include <QDebug>
#include <QMessageBox>
#include <QStringList>
#include <QCryptographicHash>

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


    bool insertSharedFile(const QString &filePath, const QString &fileName, const QString &shareToken);
    QStringList getSharedFilesByShareToken(const QString &shareToken);
    int getPasswordIdByPassword(const QString &password);


private:
    DBMySQL(); // 构造函数私有
    ~DBMySQL(); // 析构函数私有
    DBMySQL(const DBMySQL&) = delete; // 禁用复制构造函数
    DBMySQL& operator=(const DBMySQL&) = delete; // 禁用赋值运算符

    QSqlDatabase dbmysql;
};

#endif // DBMYSQL_H
