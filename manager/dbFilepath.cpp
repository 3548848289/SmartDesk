#include "dbFilepath.h"
dbFilepath::dbFilepath(const QString &dbName)
    : dbManager(dbName)  // 调用基类的构造函数，初始化数据库连接
{
    // 这里不需要再手动初始化 dbsqlite，因为已经通过父类构造函数完成了初始化
}

dbFilepath::~dbFilepath()
{

}

// 添加文件路径
bool dbFilepath::addFilePath(const QString &filePath, int &fileId) {
    QSqlQuery query(dbsqlite); // 使用父类的 dbsqlite
    query.prepare("INSERT INTO FilePaths (file_path) VALUES (:filePath)");
    query.bindValue(":filePath", filePath);

    if (!query.exec()) {
        qDebug() << "插入文件路径失败：" << query.lastError().text();
        return false;
    }
    fileId = query.lastInsertId().toInt();
    return true;
}

// 根据文件路径获取文件 ID
bool dbFilepath::getFileId(const QString &filePath, int &fileId) {
    QSqlQuery query(dbsqlite);

    query.prepare("SELECT id FROM FilePaths WHERE file_path = :filePath");
    query.bindValue(":filePath", filePath);

    if (query.exec() && query.next()) {
        fileId = query.value(0).toInt();
        return true;
    }
    return false;
}

QList<FilePathInfo> dbFilepath::searchFiles(const QString &keyword) {
    QList<FilePathInfo> fileInfos;
    QSqlQuery query(dbsqlite);

    // 查询文件路径、标签、到期时间和注释
    query.prepare("SELECT DISTINCT fp.file_path, t.tag_name, fp.expiration_date, t.annotation "
                  "FROM FilePaths fp "
                  "LEFT JOIN Tags t ON fp.id = t.file_id "
                  "WHERE fp.file_path LIKE :keyword OR t.tag_name LIKE :keyword");
    query.bindValue(":keyword", "%" + keyword + "%");
    query.exec();

    while (query.next()) {
        FilePathInfo fileInfo;

        fileInfo.filePath = query.value(0).toString();
        fileInfo.tagName = query.value(1).toString();
        fileInfo.expirationDate = query.value(2).toDateTime();
        fileInfo.annotation = query.value(3).toString();

        fileInfos << fileInfo;
    }

    return fileInfos;
}



// 获取所有文件路径
QStringList dbFilepath::getAllFilePaths() {
    QStringList filePaths;
    if (!open()) {  // 确保数据库连接正常
        qDebug() << "数据库连接初始化失败";
        return filePaths;
    }

    QSqlQuery query(dbsqlite);  // 使用数据库连接执行查询
    if (!query.exec("SELECT file_path FROM FilePaths")) {
        qDebug() << "查询失败：" << query.lastError().text();
        return filePaths;
    }

    while (query.next()) {
        filePaths.append(query.value(0).toString());
    }
    return filePaths;
}


bool dbFilepath::saveTags(int fileId, const QStringList &tags) {
    QSqlQuery query(dbsqlite);

    // 删除已有的标签，确保每次保存时是重新保存标签
    query.prepare("DELETE FROM Tags WHERE file_id = :fileId");
    query.bindValue(":fileId", fileId);
    if (!query.exec()) {
        qWarning() << "Failed to delete tags for fileId" << fileId;
        return false;
    }

    // 插入新的标签，避免重复插入
    query.prepare("INSERT INTO Tags (file_id, tag_name) VALUES (:fileId, :tagName)");
    for (const QString &tag : tags) {
        query.bindValue(":fileId", fileId);
        query.bindValue(":tagName", tag);
        if (!query.exec()) {
            qWarning() << "Failed to insert tag:" << tag;
            return false;
        }
    }

    return true;
}

bool dbFilepath::deleteTag(int fileId) {
    QSqlDatabase::database().transaction();

    QSqlQuery deleteTagQuery(dbsqlite);
    deleteTagQuery.prepare("DELETE FROM Tags WHERE file_id = :file_id");
    deleteTagQuery.bindValue(":file_id", fileId);
    bool tagDeleted = deleteTagQuery.exec();

    QSqlQuery deleteAnnotationQuery(dbsqlite);
    deleteAnnotationQuery.prepare("DELETE FROM Annotations WHERE file_id = :file_id");
    deleteAnnotationQuery.bindValue(":file_id", fileId);
    bool annotationDeleted = deleteAnnotationQuery.exec();

    QSqlQuery deleteFilePathQuery(dbsqlite);
    deleteFilePathQuery.prepare("DELETE FROM FilePaths WHERE id = :file_id");
    deleteFilePathQuery.bindValue(":file_id", fileId);
    bool filePathDeleted = deleteFilePathQuery.exec();

    if (!(tagDeleted && annotationDeleted && filePathDeleted)) {
        QSqlDatabase::database().rollback();
        return false;
    }

    QSqlDatabase::database().commit();
    return true;
}

bool dbFilepath::updateFilePath(const QString &newFilePath, const QString &oldFilePath)
{
    QSqlQuery query(dbsqlite);

    // 执行更新操作，将旧的文件路径替换成新的文件路径
    query.prepare("UPDATE FilePaths SET file_path = :newFilePath WHERE file_path = :oldFilePath");
    query.bindValue(":newFilePath", newFilePath);
    query.bindValue(":oldFilePath", oldFilePath);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Error updating file path: " << query.lastError();
        return false;
    }
}

bool dbFilepath::updateFileInfo(const FilePathInfo& fileInfo)
{

    QSqlQuery query(dbsqlite);
    dbsqlite.transaction();
    query.prepare("UPDATE FilePaths SET expiration_date = :expiration_date WHERE file_path = :file_path");
    query.bindValue(":file_path", fileInfo.filePath);
    query.bindValue(":expiration_date", fileInfo.expirationDate.toString("yyyy-MM-dd HH:mm:ss"));

    if (!query.exec()) {
        dbsqlite.rollback();
        return false;
    }

    query.prepare("SELECT id FROM FilePaths WHERE file_path = :file_path");
    query.bindValue(":file_path", fileInfo.filePath);
    if (!query.exec() || !query.next()) {
        dbsqlite.rollback();
        return false;
    }

    int fileId = query.value(0).toInt();

    query.prepare("UPDATE Tags SET tag_name = :tag WHERE file_id = :file_id");
    query.bindValue(":tag", fileInfo.tagName);
    query.bindValue(":file_id", fileId);

    if (!query.exec()) {
        dbsqlite.rollback();
        return false;
    }

    query.prepare("UPDATE Annotations SET annotation = :annotation WHERE file_id = :file_id");
    query.bindValue(":annotation", fileInfo.annotation);
    query.bindValue(":file_id", fileId);

    if (!query.exec()) {
        dbsqlite.rollback();
        return false;
    }

    dbsqlite.commit();
    return true;
}


bool dbFilepath::saveAnnotation(int fileId, const QString &annotation) {
    QSqlQuery query(dbsqlite);

    query.prepare("INSERT OR REPLACE INTO Annotations (file_id, annotation) VALUES (:fileId, :annotation)");
    query.bindValue(":fileId", fileId);
    query.bindValue(":annotation", annotation);
    return query.exec();
}


void dbFilepath::saveExpirationDate(int fileId, const QDateTime &expirationDateTime) {
    QSqlQuery query(dbsqlite);

    query.prepare("UPDATE FilePaths SET expiration_date = :expiration_date WHERE id = :file_id");
    query.bindValue(":expiration_date", expirationDateTime);
    query.bindValue(":file_id", fileId);
    query.exec();
}

bool dbFilepath::hasTagsForFile(const QString &filePath) const
{
    QSqlQuery query(dbsqlite);
    query.prepare("SELECT COUNT(*) FROM FilePaths WHERE file_path = :filePath");
    query.bindValue(":filePath", filePath);

    if (!query.exec()) {
        qDebug() << "Database query error:" << query.lastError().text();
        return false;
    }

    if (query.next())
        return query.value(0).toInt() > 0;
    return false;
}

QStringList dbFilepath::getAllTags() {
    QStringList tags;
    QSqlQuery query(dbsqlite);

    if (query.exec("SELECT DISTINCT tag_name FROM Tags")) {
        while (query.next()) {
            tags << query.value(0).toString();
        }
    }
    return tags;

}


QList<FilePathInfo> dbFilepath::getFilePathsByTag(const QString &tag) {
    QList<FilePathInfo> filePathsWithTags;
    QSqlQuery query(dbsqlite);

    if (tag == "刷新") {
        query.prepare("SELECT DISTINCT fp.file_path, t.tag_name, fp.expiration_date, a.annotation "
                      "FROM FilePaths fp "
                      "LEFT JOIN Tags t ON fp.id = t.file_id "
                      "LEFT JOIN Annotations a ON fp.id = a.file_id");
    } else {
        query.prepare("SELECT DISTINCT fp.file_path, t.tag_name, fp.expiration_date, a.annotation "
                      "FROM FilePaths fp "
                      "LEFT JOIN Tags t ON fp.id = t.file_id "
                      "LEFT JOIN Annotations a ON fp.id = a.file_id "
                      "WHERE t.tag_name = :tag");
        query.bindValue(":tag", tag);
    }

    query.exec();

    while (query.next()) {
        FilePathInfo info;
        info.filePath = query.value(0).toString();
        info.tagName = query.value(1).toString();
        info.expirationDate = query.value(2).toDateTime();
        info.annotation = query.value(3).toString();  // 获取批注内容

        filePathsWithTags.append(info);
    }

    return filePathsWithTags;
}

bool dbFilepath::getTags(int fileId, QStringList &tags) {
    QSqlQuery query(dbsqlite);

    query.prepare("SELECT tag_name FROM Tags WHERE file_id = :fileId");
    query.bindValue(":fileId", fileId);

    if (query.exec()) {
        while (query.next())
            tags.append(query.value(0).toString());
        return true;
    }
    return false;
}

bool dbFilepath::getAnnotation(int fileId, QString &annotation) {
    QSqlQuery query(dbsqlite);

    query.prepare("SELECT annotation FROM Annotations WHERE file_id = :fileId");
    query.bindValue(":fileId", fileId);

    if (query.exec() && query.next()) {
        annotation = query.value(0).toString();
        return true;
    }
    return false;
}

