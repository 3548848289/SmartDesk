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

// 根据关键字搜索文件路径
QStringList dbFilepath::searchFiles(const QString &keyword) {
    QStringList filePaths;
    QSqlQuery query(dbsqlite);

    query.prepare("SELECT DISTINCT file_path FROM FilePaths fp "
                  "LEFT JOIN Tags t ON fp.id = t.file_id "
                  "WHERE file_path LIKE :keyword OR t.tag_name LIKE :keyword");
    query.bindValue(":keyword", "%" + keyword + "%");
    query.exec();

    while (query.next()) {
        filePaths << query.value(0).toString();
    }
    return filePaths;
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
