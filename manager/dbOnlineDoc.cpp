#include "dbOnlineDoc.h"


dbOnlineDoc::dbOnlineDoc(const QString &dbName) : dbManager(dbName)
{

}


QStringList dbOnlineDoc::getSharedFilesByShareToken(const QString &shareToken) {
    QSqlQuery query(dbsqlite);

    query.prepare(R"(
        SELECT remote_file_name, local_file_path FROM shared_file WHERE share_token = :share_token
    )");
    query.bindValue(":share_token", shareToken);

    QStringList fileList;

    if (query.exec()) {
        while (query.next()) {
            QString remoteFileName = query.value(0).toString();  // 远程文件名
            QString localFilePath = query.value(1).toString();   // 本地文件路径
            fileList.append(remoteFileName + " " + localFilePath);  // 用空格分隔文件名和路径
        }
    } else {
        qDebug() << "Failed to retrieve shared files: " << query.lastError().text();
    }

    return fileList;
}
