#include "dbBackupRecord.h"

dbBackupRecord::dbBackupRecord(const QString &dbName) : dbManager(dbName) { }

dbBackupRecord::~dbBackupRecord() { }

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

QString dbBackupRecord::getInitPath(const QString &remoteFileName)
{
    QSqlQuery query(dbsqlite);
    query.prepare("SELECT Submissions.file_path "
                  "FROM Submissions "
                  "JOIN SubmissionRecords ON SubmissionRecords.submission_id = Submissions.id "
                  "WHERE SubmissionRecords.remote_file_name = :remoteFileName");

    query.bindValue(":remoteFileName", remoteFileName);

    if (query.exec() && query.next())
    {
        return query.value(0).toString();
    } else {
        qDebug() << "查询失败或没有找到数据";
        return QString();
    }
}

QDateTime dbBackupRecord::getSubTime(const QString &remoteFileName)
{
    QSqlQuery query(dbsqlite);
    query.prepare("SELECT SubmissionRecords.submit_time "
                  "FROM SubmissionRecords "
                  "WHERE SubmissionRecords.remote_file_name = :remoteFileName");

    query.bindValue(":remoteFileName", remoteFileName);

    if (query.exec() && query.next()) {
        return query.value(0).toDateTime();
    } else {
        qDebug() << "查询失败或没有找到数据";
        return QDateTime();
    }
}

QList<QString> dbBackupRecord::getAllFileNames()
{
    QList<QString> fileNames;
    QSqlQuery query(dbsqlite);
    query.prepare("SELECT file_path FROM Submissions");

    if (query.exec()) {
        while (query.next()) {
            fileNames.append(query.value(0).toString());
        }
    } else {
        qDebug() << "查询失败: " << query.lastError();
    }

    return fileNames;
}

QList<QString> dbBackupRecord::getBackupFileNames(const QString &filePath)
{
    QList<QString> backupFileNames;
    QSqlQuery query(dbsqlite);

    query.prepare("SELECT remote_file_name FROM SubmissionRecords "
                  "WHERE submission_id = (SELECT id FROM Submissions WHERE file_path = :filePath)");

    query.bindValue(":filePath", filePath);

    if (query.exec()) {
        while (query.next()) {
            backupFileNames.append(query.value(0).toString());
        }
    } else {
        qDebug() << "查询失败: " << query.lastError();
    }

    return backupFileNames;
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

bool dbBackupRecord::deleteBackupRecord(const QString &filePath) {
    QSqlQuery query(dbsqlite);
    if (!dbsqlite.transaction()) {
        qDebug() << "Failed to start transaction: " << dbsqlite.lastError().text();
        return false;
    }
    query.prepare("SELECT submission_id FROM SubmissionRecords WHERE remote_file_name = :filePath");
    query.bindValue(":filePath", filePath);
    if (!query.exec() || !query.next()) {
        qDebug() << "Failed to get submission_id:" << query.lastError();
        QSqlDatabase::database().rollback();
        return false;
    }
    int submissionId = query.value(0).toInt();

    query.prepare("DELETE FROM SubmissionRecords WHERE remote_file_name = :filePath");
    query.bindValue(":filePath", filePath);
    if (!query.exec()) {
        qDebug() << "Failed to delete from SubmissionRecords:" << query.lastError();
        QSqlDatabase::database().rollback();
        return false;
    }

    query.prepare("SELECT COUNT(*) FROM SubmissionRecords WHERE submission_id = :submissionId");
    query.bindValue(":submissionId", submissionId);
    if (!query.exec() || !query.next()) {
        qDebug() << "Failed to check remaining records:" << query.lastError();
        QSqlDatabase::database().rollback();
        return false;
    }

    int count = query.value(0).toInt();
    if (count == 0) {
        query.prepare("DELETE FROM Submissions WHERE id = :submissionId");
        query.bindValue(":submissionId", submissionId);
        if (!query.exec()) {
            qDebug() << "Failed to delete from Submissions:" << query.lastError();
            QSqlDatabase::database().rollback();
            return false;
        }
    }

    if (!dbsqlite.commit()) {
        qDebug() << "Failed to commit transaction: " << dbsqlite.lastError().text();
        dbsqlite.rollback();  // 回滚事务
        return false;
    }
    return true;
}


bool dbBackupRecord::updateFilePath(const QString &oldFilePath, const QString &newFilePath)
{
    if (newFilePath.isEmpty()) {
        qDebug() << "New file path cannot be empty!";
        return false;
    }
    QSqlQuery query(dbsqlite);

    query.prepare("UPDATE SubmissionRecords SET remote_file_name = :newFilePath WHERE remote_file_name = :oldFilePath");
    query.bindValue(":newFilePath", newFilePath);
    query.bindValue(":oldFilePath", oldFilePath);

    if (!query.exec()) {
        qDebug() << "Failed to update SubmissionRecords remote_file_name:" << query.lastError();
        return false;
    }
    return true;
}

bool dbBackupRecord::updateSubmissions(const QString &oldFilePath, const QString &newFilePath)
{
    qDebug() << oldFilePath << newFilePath;
    QSqlQuery query(dbsqlite);
    query.prepare("UPDATE Submissions SET file_path = :newFilePath WHERE file_path = :oldFilePath");
    query.bindValue(":newFilePath", newFilePath);
    query.bindValue(":oldFilePath", oldFilePath);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Error updating file path:" << query.lastError();
        return false;
    }
}

bool dbBackupRecord::deleteAll(const QString &filePath)
{

    QSqlQuery query(dbsqlite);
    query.prepare("SELECT id FROM Submissions WHERE file_path = :filePath");
    query.bindValue(":filePath", filePath);

    if (!query.exec() || !query.next()) {
        qDebug() << "Error fetching submission_id from Submissions:" << query.lastError();
        QSqlDatabase::database().rollback();
        return false;
    }

    int submissionId = query.value(0).toInt();

    query.prepare("DELETE FROM SubmissionRecords WHERE submission_id = :submissionId");
    query.bindValue(":submissionId", submissionId);

    if (!query.exec()) {
        qDebug() << "Error deleting from SubmissionRecords:" << query.lastError();
        QSqlDatabase::database().rollback();
        return false;
    }

    query.prepare("DELETE FROM Submissions WHERE id = :submissionId");
    query.bindValue(":submissionId", submissionId);

    if (!query.exec()) {
        qDebug() << "Error deleting from Submissions:" << query.lastError();
        QSqlDatabase::database().rollback();
        return false;
    }
    return true;

}

