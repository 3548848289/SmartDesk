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

#endif // SERVERMANAGER_H
