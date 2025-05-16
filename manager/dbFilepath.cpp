#include "dbFilepath.h"
dbFilepath::dbFilepath(const QString &dbName) : dbManager(dbName)  {}
dbFilepath::~dbFilepath(){}


bool dbFilepath::addFilePath(const QString &filePath, int &fileId) {
    QSqlQuery q(dbsqlite);
    q.prepare(ADDFILEPATH);
    q.bindValue(":filePath", filePath);

    if (!q.exec()) {
        qDebug() << "插入文件路径失败：" << q.lastError().text();
        return false;
    }
    fileId = q.lastInsertId().toInt();
    return true;
}

bool dbFilepath::getFileId(const QString &filePath, int &fileId) {
    QSqlQuery q(dbsqlite);
    q.prepare(GETFILEID);
    q.bindValue(":filePath", filePath);

    if (q.exec() && q.next()) {
        fileId = q.value(0).toInt();
        return true;
    }
    return false;
}

QList<FilePathInfo> dbFilepath::searchFiles(const QString &keyword) {
    QList<FilePathInfo> fileInfos;
    QSqlQuery q(dbsqlite);
    // 查询文件路径、标签、到期时间和注释
    q.prepare(SEARCHFILES);
    q.bindValue(":keyword", "%" + keyword + "%");
    q.exec();

    while (q.next()) {
        FilePathInfo fileInfo;

        fileInfo.filePath = q.value(0).toString();
        fileInfo.tagName = q.value(1).toString();
        fileInfo.expirationDate = q.value(2).toDateTime();
        fileInfo.annotation = q.value(3).toString();

        fileInfos << fileInfo;
    }

    return fileInfos;
}


QStringList dbFilepath::getAllFilePaths() {
    QStringList filePaths;
    QSqlQuery q(dbsqlite);
    if (!q.exec(GETALLFILEPATHS)) {
        qDebug() << "查询失败：" << q.lastError().text();
        return filePaths;
    }

    while (q.next())
        filePaths.append(q.value(0).toString());
    return filePaths;
}

bool dbFilepath::saveTags(int fileId, const QString &tag) {
    QSqlQuery q(dbsqlite);
    q.prepare(SAVETAGS1);    // 删除已有的标签，确保每次保存时是重新保存标签
    q.bindValue(":fileId", fileId);
    if (!q.exec()) {
        qWarning() << "Failed to delete tags for fileId" << fileId;
        return false;
    }
    q.prepare(SAVETAGS2);  // 插入新的标签
    q.bindValue(":fileId", fileId);
    q.bindValue(":tagName", tag.trimmed());  // 去除标签前后的空白字符
    if (!q.exec()) {
        qWarning() << "Failed to insert tag:" << tag;
        return false;
    }
    return true;
}

bool dbFilepath::saveAnnotation(int fileId, const QString &annotation) {
    QSqlQuery q(dbsqlite);
    q.prepare(SAVEANNOTATION);
    q.bindValue(":fileId", fileId);
    q.bindValue(":annotation", annotation);
    return q.exec();
}


void dbFilepath::saveExpirationDate(int fileId, const QDateTime &expirationDateTime) {
    QSqlQuery q(dbsqlite);
    q.prepare(SAVEEXPIRATIONDATE);
    q.bindValue(":expiration_date", expirationDateTime);
    q.bindValue(":file_id", fileId);
    q.exec();
}


bool dbFilepath::deleteTag(int fileId) {
    QSqlDatabase::database().transaction();

    QSqlQuery deleteTagq(dbsqlite);
    deleteTagq.prepare(DELETETAG1);
    deleteTagq.bindValue(":file_id", fileId);
    bool tagDeleted = deleteTagq.exec();

    QSqlQuery deleteAnnotationq(dbsqlite);
    deleteAnnotationq.prepare(DELETETAG2);
    deleteAnnotationq.bindValue(":file_id", fileId);
    bool annotationDeleted = deleteAnnotationq.exec();

    QSqlQuery deleteFilePathq(dbsqlite);
    deleteFilePathq.prepare(DELETETAG3);
    deleteFilePathq.bindValue(":file_id", fileId);
    bool filePathDeleted = deleteFilePathq.exec();

    if (!(tagDeleted && annotationDeleted && filePathDeleted)) {
        QSqlDatabase::database().rollback();
        return false;
    }

    QSqlDatabase::database().commit();
    return true;
}

bool dbFilepath::updateFilePath(const QString &newFilePath, const QString &oldFilePath)
{
    QSqlQuery q(dbsqlite);
    q.prepare(UPDATEFILEPATH);
    q.bindValue(":newFilePath", newFilePath);
    q.bindValue(":oldFilePath", oldFilePath);

    if (q.exec()) {
        return true;
    } else {
        qDebug() << "Error updating file path: " << q.lastError();
        return false;
    }
}

bool dbFilepath::updateFileInfo(const FilePathInfo& fileInfo)
{

    QSqlQuery q(dbsqlite);
    dbsqlite.transaction();
    q.prepare(UPDATEFILEINFO1);
    q.bindValue(":file_path", fileInfo.filePath);
    q.bindValue(":expiration_date", fileInfo.expirationDate.toString("yyyy-MM-dd HH:mm:ss"));

    if (!q.exec()) {
        dbsqlite.rollback();
        return false;
    }

    q.prepare(UPDATEFILEINFO2);
    q.bindValue(":file_path", fileInfo.filePath);
    if (!q.exec() || !q.next()) {
        dbsqlite.rollback();
        return false;
    }

    int fileId = q.value(0).toInt();
    q.prepare(UPDATEFILEINFO3);
    q.bindValue(":tag", fileInfo.tagName);
    q.bindValue(":file_id", fileId);

    if (!q.exec()) {
        dbsqlite.rollback();
        return false;
    }

    q.prepare(UPDATEFILEINFO4);
    q.bindValue(":annotation", fileInfo.annotation);
    q.bindValue(":file_id", fileId);

    if (!q.exec()) {
        dbsqlite.rollback();
        return false;
    }

    dbsqlite.commit();
    return true;
}


bool dbFilepath::hasTagsForFile(const QString &filePath) const
{
    QSqlQuery q(dbsqlite);
    q.prepare(HASTAGSFORFILE);
    q.bindValue(":filePath", filePath);

    if (!q.exec()) {
        qDebug() << "Database q error:" << q.lastError().text();
        return false;
    }

    if (q.next())
        return q.value(0).toInt() > 0;
    return false;
}

QStringList dbFilepath::getAllTags() {
    QStringList tags;
    QSqlQuery q(dbsqlite);

    if (q.exec(GETALLTAGS)) {
        while (q.next()) {
            tags << q.value(0).toString();
        }
    }
    return tags;

}


QList<FilePathInfo> dbFilepath::getFilePathsByTag(const QString &tag) {
    QList<FilePathInfo> filePathsWithTags;
    QSqlQuery q(dbsqlite);

    if (tag == "刷新") {
        q.prepare(GETFILEPATHSBYTAG1);
    } else {
        q.prepare(GETFILEPATHSBYTAG2);
        q.bindValue(":tag", tag);
    }

    q.exec();

    while (q.next()) {
        FilePathInfo info;
        info.filePath = q.value(0).toString();
        info.tagName = q.value(1).toString();
        info.expirationDate = q.value(2).toDateTime();
        info.annotation = q.value(3).toString();  // 获取批注内容

        filePathsWithTags.append(info);
    }

    return filePathsWithTags;
}

bool dbFilepath::getTags(int fileId, QStringList &tags) {
    QSqlQuery q(dbsqlite);

    q.prepare(GETTAGS);
    q.bindValue(":fileId", fileId);

    if (q.exec()) {
        while (q.next())
            tags.append(q.value(0).toString());
        return true;
    }
    return false;
}

bool dbFilepath::getAnnotation(int fileId, QString &annotation) {
    QSqlQuery q(dbsqlite);

    q.prepare(GETANNOTATION);
    q.bindValue(":fileId", fileId);

    if (q.exec() && q.next()) {
        annotation = q.value(0).toString();
        return true;
    }
    return false;
}

bool dbFilepath::getFileInfoByFilePath(const QString& filePath, FilePathInfo& fileInfo)
{
    QSqlQuery q(dbsqlite);
    dbsqlite.transaction();
    q.prepare(GETFILEINFOBYFILEPATH1);
    q.bindValue(":file_path", filePath);

    if (!q.exec() || !q.next()) {
        dbsqlite.rollback();
        return false;
    }

    fileInfo.filePath = filePath;
    fileInfo.expirationDate = QDateTime::fromString(q.value(0).toString(), "yyyy-MM-dd'T'HH:mm:ss.zzz");
    qDebug() << fileInfo.expirationDate;
    q.prepare(GETFILEINFOBYFILEPATH2);
    q.bindValue(":file_path", filePath);

    if (!q.exec() || !q.next()) {
        dbsqlite.rollback();
        return false;
    }

    fileInfo.tagName = q.value(0).toString();

    q.prepare(GETFILEINFOBYFILEPATH3);
    q.bindValue(":file_path", filePath);

    if (!q.exec() || !q.next()) {
        dbsqlite.rollback();
        return false;
    }

    fileInfo.annotation = q.value(0).toString();
    dbsqlite.commit();
    return true;
}



