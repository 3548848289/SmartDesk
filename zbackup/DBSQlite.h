#ifndef DBSQLITE_H
#define DBSQLITE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include <QStringList>
#include <QDateTime>
#include <QDebug>
#include <QVector>
#include <QPair>

struct FilePathInfo {
    QString filePath;
    QString tagName;
    QDateTime expirationDate;
};

class DBSQlite {
public:
    static DBSQlite& instance(const QString &dbName = "D:/dbList/DataGrip 2023.2/myDgPro/mytxt/file_metadata.db") {
        static DBSQlite instance(dbName);
        instance.initializeDatabase();
        return instance;
    }

    bool open();
    void close();

    // 文件路径管理
    bool addFilePath(const QString &filePath, int &fileId);
    bool getFileId(const QString &filePath, int &fileId);
    QStringList getAllFilePaths();
    QStringList searchFiles(const QString &keyword);

    // 标签管理
    bool getTags(int fileId, QStringList &tags);
    QStringList getAllTags();
    bool saveTags(int fileId, const QStringList &tags);
    bool hasTagsForFile(const QString &filePath) const;
    QList<FilePathInfo> getFilePathsByTag(const QString &tag);

    // 注释管理
    bool getAnnotation(int fileId, QString &annotation);
    bool saveAnnotation(int fileId, const QString &annotation);

    // 过期日期管理
    void saveExpirationDate(int fileId, const QDateTime &expirationDateTime);
    QVector<QPair<QString, QDateTime>> getSortByExp();

    QString lastError() const;

private:
    DBSQlite(const QString &dbName);
    ~DBSQlite();
    DBSQlite(const DBSQlite&) = delete; // 禁用复制构造函数
    DBSQlite& operator=(const DBSQlite&) = delete; // 禁用赋值运算符

    QSqlDatabase dbsqlite;
    void initializeDatabase();
};

#endif // DBSQLITE_H
