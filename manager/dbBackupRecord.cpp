#include "dbBackupRecord.h"

dbBackupRecord::dbBackupRecord(const QString &dbName)
    : dbManager(dbName)  // 调用基类的构造函数，初始化数据库连接
{
    // 这里不需要再手动初始化 dbsqlite，因为已经通过父类构造函数完成了初始化
}


dbBackupRecord::~dbBackupRecord() {

}

void dbBackupRecord::recordSubmission(const QString &filePath, const QString &backupFilePath) {

    QSqlQuery query(dbsqlite);
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    // 检查文件是否已有提交记录
    query.prepare("SELECT id FROM Submissions WHERE file_path = :filePath");
    query.bindValue(":filePath", filePath);
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
        return;
    }

    int submissionId = -1;
    if (query.next()) {
        submissionId = query.value(0).toInt();     // 如果已有记录，获取ID
    } else {
        // 没有记录，插入新记录并获取 ID
        query.prepare("INSERT INTO Submissions (file_path, submit_time) VALUES (:filePath, :submitTime)");
        query.bindValue(":filePath", filePath);
        query.bindValue(":submitTime", currentTime);

        if (!query.exec()) {
            qDebug() << "Insert into Submissions failed:" << query.lastError();
            return;
        }
        submissionId = query.lastInsertId().toInt();
    }

    // 插入记录到 SubmissionRecords 表
    query.prepare("INSERT INTO SubmissionRecords (submission_id, remote_file_name, submit_time) "
                  "VALUES (:submissionId, :backupFilePath, :submitTime)");
    query.bindValue(":submissionId", submissionId);
    query.bindValue(":backupFilePath", backupFilePath);
    query.bindValue(":submitTime", currentTime);

    if (!query.exec()) {
        qDebug() << "Insert into SubmissionRecords failed:" << query.lastError();
    } else {
        qDebug() << "Record added for submission ID:" << submissionId << " with remote file name:" << backupFilePath;
    }
}

QList<QString> dbBackupRecord::getRecordSub(const QString& filePath) {
    QSqlQuery query(dbsqlite);

    query.prepare("SELECT sr.remote_file_name "
                  "FROM SubmissionRecords sr "
                  "JOIN Submissions s ON sr.submission_id = s.id "
                  "WHERE s.file_path = :filePath");

    query.bindValue(":filePath", filePath);

    QList<QString> filePaths;
    if (query.exec()) {
        while (query.next()) {
            QString remoteFilePath = query.value(0).toString();
            filePaths.append(remoteFilePath);
        }
        for (const QString &path : filePaths) {
            qDebug() << "File Path: " << path;
        }
    } else {
        qDebug() << "Query failed: " << query.lastError().text();
    }
    return filePaths;
}

bool dbBackupRecord::hasSubmissions(const QString& filePath) const {
    QSqlQuery query(dbsqlite);
    query.prepare("SELECT COUNT(*) FROM Submissions WHERE file_path = :filePath");
    query.bindValue(":filePath", filePath);

    if (!query.exec()) {
        qDebug() << "dbBackupRecord::hasSubmissions Query failed:" << query.lastError();
        return false;
    }
    if (query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}




bool dbBackupRecord::insertSharedFile(const QString &filePath, const QString &fileName, const QString &shareToken) {
    QSqlQuery query(dbsqlite);

    // 准备 INSERT 语句，并包含 share_token
    query.prepare("INSERT INTO SharedFiles (local_file_path, remote_file_name, share_token) "
                  "VALUES (:local_file_path, :remote_file_name, :share_token)");
    query.bindValue(":local_file_path", filePath);
    query.bindValue(":remote_file_name", fileName);
    query.bindValue(":share_token", shareToken);  // 确保绑定了 share_token 的值

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "插入共享文件失败: " << query.lastError().text();
        return false;
    }
}



int dbBackupRecord::getPasswordIdByPassword(const QString &password) {
    QSqlQuery query(dbsqlite);

    query.prepare("SELECT id FROM users WHERE password = :password");
    query.bindValue(":password", password);  // 绑定用户提供的口令

    if (query.exec() && query.next()) {
        return query.value(0).toInt();  // 返回匹配的 passwordId
    } else {
        qDebug() << "Failed to retrieve password ID: " << query.lastError().text();
        return -1;  // 如果查询失败，返回 -1
    }
}

QStringList dbBackupRecord::getSharedFilesByShareToken(const QString &shareToken) {
    QSqlQuery query(dbsqlite);

    query.prepare(R"(
        SELECT remote_file_name, local_file_path
        FROM SharedFiles
        WHERE share_token = :share_token
    )");
    query.bindValue(":share_token", shareToken);
    qDebug() << shareToken;

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
