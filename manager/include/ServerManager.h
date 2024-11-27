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

class ServerManager : public QObject {
    Q_OBJECT

public:
    static ServerManager* instance() {
        static ServerManager* instance = new ServerManager();
        return instance;
    }


    // 删除拷贝构造函数和赋值操作符
    ServerManager(const ServerManager&) = delete;
    ServerManager& operator=(const ServerManager&) = delete;

    bool commitToServer(const QString& fileName, const QString& tag);
    void getCommitHistory(const QModelIndex& index, QAbstractItemModel* model);
    void setCurdir(const QString& curdir);
    void downloadFile(const QString& fileName);
    void getFilesInDirectory(const QModelIndex& index, QAbstractItemModel* model);

    void onListFilesFinished(QNetworkReply* reply);

    void sendfilepaths(QList<QString> filepaths);
signals:
    void commitSuccess();
    void commitFailed();
    void historyReceived(const QStringList& history);
    void onFilesListUpdated(const QStringList& files);

private slots:
    void onDownloadFinished(QNetworkReply* reply, const QString& fileName);
    void onUploadFinished(QNetworkReply* reply);

private:
    explicit ServerManager(QObject *parent = nullptr) : QObject(parent) {}
    ~ServerManager() = default; // 确保单例的析构函数是私有的

    QNetworkAccessManager networkManager; // 用于处理网络请求
    QString m_curdir;
};

#endif // SERVERMANAGER_H
