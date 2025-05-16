#include "ServerManager.h"
#include <QDir>
#include <QFile>
#include <QDebug>

void ServerManager::sendfilepath(QString filepath)
{
    emit onFilesListUpdated(filepath);
}

void ServerManager::test(const QString &filepath)
{
    qDebug() << filepath;
}


void ServerManager::commitFile(const QString& filepath) {
    QFileInfo fileInfo(filepath);
    QString filename = fileInfo.fileName();
    QString urlStr = QString("http://127.0.0.1:5000/%1").arg(filename);

    QUrl url(urlStr);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");

    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file:" << filepath;
        QMessageBox::information(nullptr, "失败", "该文件无法打开!", QMessageBox::Ok);
        return;
    }
    QByteArray fileData = file.readAll();
    file.close();
    QNetworkReply* reply = networkManager.put(request, fileData);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        oncommitFin(reply);
    });
}

void ServerManager::oncommitFin(QPointer<QNetworkReply> reply)
{
    if (!reply) {
        QMessageBox::critical(nullptr, "上传失败", "网络响应无效！");
        return;
    }
    if (reply->error() == QNetworkReply::NoError) {
        QMessageBox::information(nullptr, "成功", "文件已经上传至云端");
    } else {
        QString error = reply->errorString();
        QMessageBox::critical(nullptr, "上传失败", error);
        emit commitFailed();
    }

    reply->deleteLater();
}


void ServerManager::downloadFile(const QString& filepath) {
    QFileInfo fileInfo(filepath);
    QString filename = fileInfo.fileName();
    QString url = QString("http://127.0.0.1:5000/uploads/%1").arg(filename);
    QNetworkRequest request{QUrl(url)};
    QNetworkReply* reply = networkManager.get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply, filepath]() {
        ondownloadFin(reply, filepath);
    });
}

void ServerManager::ondownloadFin(QNetworkReply* reply, const QString& filepath) {
    if (reply->error() != QNetworkReply::NoError) {
        QMessageBox::critical(nullptr, "下载失败", "出现错误：\n" + reply->errorString());
        return;
    }
    QByteArray data = reply->readAll();
    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(nullptr, "无法保存", filepath, QMessageBox::Ok);
        return;
    }
    file.write(data);
    file.close();
    reply->deleteLater();
    QMessageBox::information(nullptr, tr("成功"), tr("文件下载成功"));
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
        QMessageBox::critical(nullptr, "获取失败", "出现错误：\n" + reply->errorString());
        reply->deleteLater();
        return;
    }
    QByteArray response = reply->readAll();
    QStringList fileNames = QString(response).split('\n', Qt::SkipEmptyParts);

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

                emit historyReceived(fileList);
            }
        } else {
            qDebug() << "getSharedFile error:" << reply->errorString();
            emit commitFailed();
        }
        reply->deleteLater();
    });
}



bool ServerManager::setSharedFile(const QString& filepath, const QString& shareToken) {
    QFileInfo fileInfo(filepath);
    QString filename = fileInfo.fileName();
    QString urlStr = QString("http://127.0.0.1:5000/%1?share_token=%2").arg(filename, shareToken);

    QUrl url(urlStr);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");

    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(nullptr, "失败", "该文件无法打开!", QMessageBox::Ok);
        return false;
    }
    QByteArray fileData = file.readAll();
    file.close();

    QPointer<QNetworkReply> reply = networkManager.put(request, fileData);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError)
            QMessageBox::information(nullptr, "成功", "共享文件已上传!", QMessageBox::Ok);
        else
            qDebug() << "Upload failed:" << reply->errorString();
        reply->deleteLater();
    });

    return true;
}

void ServerManager::checkFileExists(const QString& filepath) {
    QFileInfo fileInfo(filepath);
    QString filename = fileInfo.fileName();
    QString url = QString("http://127.0.0.1:5000/exists/%1").arg(QUrl::toPercentEncoding(filename));

    QNetworkRequest request{QUrl(url)};
    QNetworkReply* reply = networkManager.get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, filepath]() {
        bool exists = false;
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(response);
            exists = doc.object().value("exists").toBool();
        } else {
            // qDebug() << "Error checking file existence:" << reply->errorString();
        }
        emit returnStatus(exists);
        reply->deleteLater();
    });
}

