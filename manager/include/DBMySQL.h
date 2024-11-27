#ifndef DBMYSQL_H
#define DBMYSQL_H


#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include <QString>
#include <QVariant>
#include <QDate>
#include <QMap>
#include <QDebug>
#include <QMessageBox>
#include <QStringList>
#include <QCryptographicHash>
#include <QFileInfo>

class DBMySQL {
public:
    static DBMySQL& instance() {
        static DBMySQL instance; // 懒汉式单例
        return instance;
    }

    bool open();
    void close();
    bool createTable();


    QString lastError() const;

    void recordSubmission(const QString &filePath, const QString &backupFilePath);
    QList<QString> getRecordSub(const QString& filePath);

    bool hasSubmissions(const QString& filePath) const;


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
