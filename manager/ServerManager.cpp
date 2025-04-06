#include "ServerManager.h"
#include <QDir>
#include <QFile>
#include <QDebug>

void ServerManager::setCurdir(const QString &curdir)
{
    m_curdir = curdir;
}

void ServerManager::sendfilepath(QString filepath)
{
    emit onFilesListUpdated(filepath);
}

void ServerManager::test(const QString &filepath)
{
    qDebug() << filepath;
}


bool ServerManager::commitFile(const QString& filepath) {
    QFileInfo fileInfo(filepath);
    QString filename = fileInfo.fileName();
    QString urlStr = QString("http://127.0.0.1:5000/%1").arg(filename);

    QUrl url(urlStr);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");

    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file:" << filepath;
        emit commitFailed();
        return false;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QPointer<QNetworkReply> reply = networkManager.put(request, fileData);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Upload success:" << reply->readAll();
            emit commitSuccess();
        } else {
            qDebug() << "Upload failed:" << reply->errorString();
            emit commitFailed();
        }
        reply->deleteLater();
    });

    return true;
}


void ServerManager::oncommitFin(QPointer<QNetworkReply> reply)
{
    if (!reply) {
        qWarning() << "Reply is invalid.";
        emit commitFailed();
        return;
    }

    if (reply->error() == QNetworkReply::NoError) {
        emit commitSuccess();
        qDebug() << "提交成功";
    } else {
        qWarning() << "Upload failed:" << reply->errorString();
        emit commitFailed();
    }

    reply->deleteLater();
}

bool ServerManager::downloadFile(const QString& filepath) {
    QFileInfo fileInfo(filepath);
    QString filename = fileInfo.fileName();  // 获取文件名
    QString url = QString("http://127.0.0.1:5000/uploads/%1").arg(filename);  // 生成 URL
    QNetworkRequest request{QUrl(url)};
    QNetworkReply* reply = networkManager.get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, filepath]() {
        ondownloadFin(reply, filepath);
    });

    return true;
}

void ServerManager::ondownloadFin(QNetworkReply* reply, const QString& filepath) {
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Download error:" << reply->errorString();
        return;
    }

    QByteArray data = reply->readAll();
    QFile file(filepath);  // 使用传入的 filepath 保存文件
    qDebug() << filepath;  // 打印目标路径
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to save file to:" << filepath;
        return;
    }

    file.write(data);  // 将数据写入文件
    file.close();
    reply->deleteLater();
}



void ServerManager::getHistory() {
    QString baseHttpUrl = "http://127.0.0.1:5000/list/";
    QNetworkRequest request{QUrl(baseHttpUrl)};

    QNetworkReply* reply = networkManager.get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onhistoryFin(reply);
    });
}

void ServerManager::onhistoryFin(QNetworkReply* reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Request failed:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray response = reply->readAll();
    QStringList fileNames = QString(response).split('\n', Qt::SkipEmptyParts); // 按行分割文件名

    qDebug() << "File names:" << fileNames;

    emit fileListReady(fileNames);
    reply->deleteLater();
}





void ServerManager::getSharedFile(const QString& shareToken) {
    QUrl url("http://127.0.0.1:5000/get_shared_files?share_token=" + shareToken);
    QNetworkRequest request(url);

    QNetworkReply* reply = networkManager.get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            if (!jsonDoc.isNull()) {
                QJsonObject obj = jsonDoc.object();
                QJsonArray files = obj["files"].toArray();

                QStringList fileList;
                for (const QJsonValue &val : files) {
                    QJsonObject fileObj = val.toObject();
                    QString remoteFileName = fileObj["remote_file_name"].toString();
                    QString localFilePath = fileObj["local_file_path"].toString();
                    fileList.append(remoteFileName + " " + localFilePath);
                }

                emit historyReceived(fileList);  // 可以用现有信号传出
            }
        } else {
            qDebug() << "getSharedFile error:" << reply->errorString();
            emit commitFailed();  // 你也可以定义一个新的错误信号
        }
        reply->deleteLater();
    });
}



bool ServerManager::setSharedFile(const QString& filepath, const QString& shareToken) {
    QFileInfo fileInfo(filepath);
    QString filename = fileInfo.fileName();
    QString urlStr = QString("http://127.0.0.1:5000/%1?share_token=%2")
                         .arg(filename, shareToken);

    QUrl url(urlStr);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");

    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file:" << filepath;
        emit commitFailed();
        return false;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QPointer<QNetworkReply> reply = networkManager.put(request, fileData);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Upload success:" << reply->readAll();
            emit commitSuccess();
        } else {
            qDebug() << "Upload failed:" << reply->errorString();
            emit commitFailed();
        }
        reply->deleteLater();
    });

    return true;
}
