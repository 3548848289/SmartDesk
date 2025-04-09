// ServerManager.h
#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <QObject>


#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QHttpMultiPart>
#include <QtNetwork/QNetworkRequest>

#include <QModelIndex>
#include <QAbstractItemModel>
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <QFileInfo>
#include <QString>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QRegularExpression>
#include <QPointer>
#include <QMessageBox>
class ServerManager : public QObject {
    Q_OBJECT

public:
    static ServerManager* instance() {
        static ServerManager* instance = new ServerManager();
        return instance;
    }
    ServerManager(const ServerManager&) = delete;
    ServerManager& operator=(const ServerManager&) = delete;

    void test(const QString& filepath);
    void setCurdir(const QString& curdir);
    void sendfilepath(QString filepath);

    void commitFile(const QString& filepath);
    void downloadFile(const QString& filepath);
    void getHistory();
    bool setSharedFile(const QString &filepath, const QString &shareToken);
    void getSharedFile(const QString& shareToken);
    void checkFileExists(const QString &filepath);
signals:
    void commitSuccess();
    void commitFailed();
    void historyReceived(const QStringList& history);
    void onFilesListUpdated(const QString& files);
    void fileListReady(const QStringList &fileNames);
    void returnStatus(bool exists);



private slots:
    void oncommitFin(QPointer<QNetworkReply> reply);
    void ondownloadFin(QNetworkReply* reply, const QString& fileName);
    void onhistoryFin(QNetworkReply* reply);

private:
    explicit ServerManager(QObject *parent = nullptr) : QObject(parent) {}
    ~ServerManager() = default;
    QNetworkAccessManager networkManager;
    QString m_curdir;
};

// bool commitToServer(const QString& fileName, const QString& tag);
// bool ServerManager::commitToServer(const QString& fileName, const QString& tag) {
//     QString filePath = m_curdir + '/' + fileName; // 当前目录和文件名组合成完整路径
//     if(tag == "online/") {
//         filePath = filePath.mid(1); // 处理tag为 "online/" 的情况
//     }

//     QString targetPath = QDir(QDir::currentPath()).filePath("uploads/" + QFileInfo(filePath).fileName());
//     QDir().mkpath(QFileInfo(targetPath).absolutePath()); // 创建目录（如果不存在）

//     if (QFile::exists(targetPath)) {
//         QFile::remove(targetPath); // 删除已存在的文件
//     }

//     if (QFile::copy(filePath, targetPath)) {
//         qDebug() << "File copied successfully to:" << targetPath; // 复制成功
//     } else {
//         qDebug() << "Source file path, Failed to copy file:" << filePath;
//         emit commitFailed();
//         return false;
//     }

//     QString httpUrl = "http://127.0.0.1:5000/" + tag + QFileInfo(targetPath).fileName();
//     QString trimmedDir = m_curdir.mid(3);
//     httpUrl += "?path=" + QUrl::toPercentEncoding(trimmedDir);
//     qDebug() << "Upload URL:" << httpUrl;

//     QNetworkRequest request{QUrl(httpUrl)};
//     request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");

//     QFile *file = new QFile(targetPath);
//     if (!file->open(QIODevice::ReadOnly)) {
//         qWarning() << "Failed to open file for upload:" << file->errorString();
//         emit commitFailed();
//         delete file;
//         return false;
//     }

//     QNetworkReply *reply = networkManager.put(request, file);
//     file->setParent(reply);

//     connect(reply, &QNetworkReply::finished, this, [this, reply]() {
//         onUploadFinished(reply);
//         return true;
//     });
//     return true;
// }

// void ServerManager::getFilesInDirectory(const QModelIndex& index, QAbstractItemModel* model) {
//     QString baseHttpUrl = "http://192.168.45.236:5000/list/";

//     QString dirname = model->data(index.sibling(index.row(), 0)).toString();
//     dirname.replace('.', '_');

//     QString listUrl = baseHttpUrl + dirname;
//     qDebug() << listUrl;
//     QNetworkRequest request{QUrl(listUrl)};

//     QNetworkReply *reply = networkManager.get(request);
//     connect(reply, &QNetworkReply::finished, this, [this, reply]() {
//         onListFilesFinished(reply);
//     });
// }



// void ServerManager::onListFilesFinished(QNetworkReply* reply) {
//     if (reply->error() == QNetworkReply::NoError) {
//         QByteArray responseData = reply->readAll();
//         QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);

//         if (jsonDoc.isObject()) {
//             QJsonObject jsonObj = jsonDoc.object();
//             QJsonArray fileArray = jsonObj["files"].toArray();

//             QStringList filesList;
//             for (const QJsonValue &fileValue : fileArray) {
//                 QString fileName = fileValue.toString();
//                 filesList.append(fileName);
//                 qDebug() << fileName;
//             }

//             // emit onFilesListUpdated(filesList);

//         }
//         else { qDebug() << "Invalid response format"; }
//     } else { qDebug() << "Error retrieving file list:" << reply->errorString(); }
//     reply->deleteLater();
// }

#endif // SERVERMANAGER_H
