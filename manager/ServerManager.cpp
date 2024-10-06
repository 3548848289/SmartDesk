#include "ServerManager.h"
#include <QDir>
#include <QFile>
#include <QDebug>

bool ServerManager::commitToServer(const QString& fileName, const QString& tag) {
    QString filePath = m_curdir + '/' + fileName; // 当前目录和文件名组合成完整路径
    if(tag == "online/") {
        filePath = filePath.mid(1); // 处理tag为 "online/" 的情况
    }

    QString targetPath = QDir(QDir::currentPath()).filePath("uploads/" + QFileInfo(filePath).fileName());
    QDir().mkpath(QFileInfo(targetPath).absolutePath()); // 创建目录（如果不存在）

    if (QFile::exists(targetPath)) {
        QFile::remove(targetPath); // 删除已存在的文件
    }

    if (QFile::copy(filePath, targetPath)) {
        qDebug() << "File copied successfully to:" << targetPath; // 复制成功
    } else {
        qDebug() << "Source file path, Failed to copy file:" << filePath;
        emit commitFailed();
        return false;
    }

    QString httpUrl = "http://192.168.45.236:5000/" + tag + QFileInfo(targetPath).fileName();
    QString trimmedDir = m_curdir.mid(3);
    httpUrl += "?path=" + QUrl::toPercentEncoding(trimmedDir);
    qDebug() << "Upload URL:" << httpUrl;

    QNetworkRequest request{QUrl(httpUrl)};
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");

    QFile *file = new QFile(targetPath);
    if (!file->open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open file for upload:" << file->errorString();
        emit commitFailed();
        delete file;
        return false;
    }

    QNetworkReply *reply = networkManager.put(request, file);
    file->setParent(reply);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onUploadFinished(reply);
        return true;
    });
}


void ServerManager::onUploadFinished(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        emit commitSuccess();
    } else {
        qWarning() << "Upload failed:" << reply->errorString();
        emit commitFailed();
    }
    reply->deleteLater(); // 确保 reply 在处理后被删除
}

void ServerManager::downloadFile(const QString& fileName) {
    QString dir = fileName;
    dir.replace('.', '_');
    dir.remove(QRegularExpression("_[1-9]"));

    QString url = QString("http://192.168.45.236:5000/download/%1/%2").arg(dir).arg(fileName);
    QNetworkRequest request{QUrl(url)};
    QNetworkReply* reply = networkManager.get(request);

    // 使用捕获列表传递fileName
    connect(reply, &QNetworkReply::finished, this, [this, reply, fileName]() {
        onDownloadFinished(reply, fileName);
    });
}



void ServerManager::getCommitHistory(const QModelIndex& index, QAbstractItemModel* model) {
    // 使用 HTTP(S) 替代 FTP
    QString httpUrl = "http://192.168.45.236:5000/download/";  // 需要替换成实际的 HTTP 服务器地址
    QNetworkRequest request{QUrl(httpUrl)};

    QNetworkReply *reply = networkManager.get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onDownloadFinished(reply, "");  // 改为处理下载完成
    });
}

void ServerManager::setCurdir(const QString &curdir)
{
    m_curdir = curdir;
}


void ServerManager::onDownloadFinished(QNetworkReply* reply, const QString& fileName) {
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Download error:" << reply->errorString();
        return;
    }

    QByteArray data = reply->readAll();
    QString filePath = QDir(m_curdir).filePath(fileName); // 使用完整路径保存

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to save file to:" << m_curdir;
        return;
    }

    file.write(data);
    file.close();
    reply->deleteLater();
}


void ServerManager::getFilesInDirectory(const QModelIndex& index, QAbstractItemModel* model) {
    QString baseHttpUrl = "http://192.168.45.236:5000/list/";

    QString dirname = model->data(index.sibling(index.row(), 0)).toString();
    dirname.replace('.', '_');

    QString listUrl = baseHttpUrl + dirname;
    qDebug() << listUrl;
    QNetworkRequest request{QUrl(listUrl)};

    QNetworkReply *reply = networkManager.get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onListFilesFinished(reply);
    });
}

void ServerManager::onListFilesFinished(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);

        if (jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();
            QJsonArray fileArray = jsonObj["files"].toArray();

            QStringList filesList;
            for (const QJsonValue &fileValue : fileArray) {
                QString fileName = fileValue.toString();
                filesList.append(fileName);
                qDebug() << fileName;
            }

            emit onFilesListUpdated(filesList);

        }
        else { qDebug() << "Invalid response format"; }
    } else { qDebug() << "Error retrieving file list:" << reply->errorString(); }
    reply->deleteLater();
}

