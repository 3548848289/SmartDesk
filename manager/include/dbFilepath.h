#ifndef DBFILEPATH_H
#define DBFILEPATH_H

#include <QString>
#include <QDateTime>
#include <QStringList>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "dbManager.h"

struct FilePathInfo {
    QString filePath;
    QString tagName;
    QDateTime expirationDate;
    QString annotation;
};

class dbFilepath : public dbManager {

public:
    dbFilepath(const QString &dbName);  // 构造函数声明
    ~dbFilepath();


    bool addFilePath(const QString &filePath, int &fileId);
    bool getFileId(const QString &filePath, int &fileId);
    QStringList getAllFilePaths();
    QStringList searchFiles(const QString &keyword);
    // QList<QPair<QString, QString>> searchFiles(const QString &keyword);


    bool saveTags(int fileId, const QStringList &tags);
    bool saveAnnotation(int fileId, const QString &annotation);
    void saveExpirationDate(int fileId, const QDateTime &expirationDateTime);

    bool hasTagsForFile(const QString &filePath) const;
    QStringList getAllTags();
    QList<FilePathInfo> getFilePathsByTag(const QString &tag);

    QVector<QPair<QString, QDateTime>> getSortByExp();
    bool getAnnotation(int fileId, QString &annotation);

    bool getTags(int fileId, QStringList &tags);

};


#endif // DBFILEPATH_H
