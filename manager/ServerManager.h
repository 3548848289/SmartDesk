// ServerManager.h
#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <QFileInfo>
#include <QString>
#include <QDir>
#include <QHttpMultiPart>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QRegularExpression>

class ServerManager : public QObject {
    Q_OBJECT
public:
    explicit ServerManager(QObject *parent = nullptr);
    void commitToServer(const QModelIndex& index, QAbstractItemModel* model);
    void getCommitHistory(const QModelIndex& index, QAbstractItemModel* model);
    void setCurdir(const QString& curdir);
    void downloadFile(const QString& fileName);


    void getFilesInDirectory(const QModelIndex& index, QAbstractItemModel* model);

    void onListFilesFinished(QNetworkReply* reply);

signals:

    void commitSuccess();
    void commitFailed();
    void historyReceived(const QStringList& history);
    void onFilesListUpdated(const QStringList& files);

private slots:
    void onDownloadFinished(QNetworkReply* reply, const QString& fileName);
    void onUploadFinished(QNetworkReply* reply);


private:
    QNetworkAccessManager networkManager; // 用于处理网络请求
    QString m_curdir;
};

#endif // SERVERMANAGER_H
