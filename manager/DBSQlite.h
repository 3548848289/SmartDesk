// DBSQlite.h
#ifndef DBSQLITE_H
#define DBSQLITE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include <QDebug>
#include <QDateTime>

struct FilePathInfo {
    QString filePath;
    QString tagName;
    QDateTime expirationDate;
};

class DBSQlite {
public:
    DBSQlite(const QString &dbName);
    ~DBSQlite();

    bool open();
    void close();

    // 文件路径管理
    bool addFilePath(const QString &filePath, int &fileId);
    bool getFileId(const QString &filePath, int &fileId);
    QStringList getAllFilePaths();

    // 标签管理
    bool getTags(int fileId, QStringList &tags);
    bool saveTags(int fileId, const QStringList &tags);
    QStringList getAllTags();
    bool hasTagsForFile(const QString &filePath) const;
    QList<FilePathInfo> getFilePathsByTag(const QString &tag);

    // 注释管理
    bool getAnnotation(int fileId, QString &annotation);
    bool saveAnnotation(int fileId, const QString &annotation);

    // 过期日期管理
    void saveExpirationDate(int fileId, const QDateTime &expirationDateTime);
    QVector<QPair<QString, QDateTime>> getSortByExp();

    // 文件搜索
    QStringList searchFiles(const QString &keyword);


    void recordSubmission(const QString &filePath);
    bool hasSubmissions(const QString& filePath) const;

    QString lastError() const;

private:
    QSqlDatabase dbsqlite;
    void initializeDatabase();
};

#endif // DBSQLITE_H
