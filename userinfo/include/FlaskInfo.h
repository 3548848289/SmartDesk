#ifndef FLASKINFO_H
#define FLASKINFO_H

#include <QObject>
#include "D:\\QT6\\6.8.0\\mingw_64\include\\QtNetwork\\QNetworkAccessManager"
#include "D:\\QT6\\6.8.0\\mingw_64\include\\QtNetwork\\QNetworkRequest"
#include "D:\\QT6\\6.8.0\\mingw_64\include\\QtNetwork\\QNetworkReply"

#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>
#include <QMessageBox>

class FlaskInfo : public QObject
{
    Q_OBJECT

public:
    explicit FlaskInfo(QObject *parent = nullptr);
    void route_loginUser(const QString &username, const QString &password);
    void route_registerUser(const QString &username, const QString &password, const QByteArray &avatarData);
    void route_updateUserInfo(const QString &username, const QMap<QString, QVariant> &userInfo);
    void route_loadUserInfo(const QString &username);

signals:
    void s_loginRec(const QJsonObject &response);
    void s_registerRec(const QJsonObject &response);
    void s_updateRec(const QJsonObject &response);
    void s_loadRec(const QJsonObject &response);

    void errorOccurred(const QString &error);
    void avatarDownloaded(const QByteArray &data, const QString &action);

private slots:

    void H_LoginAct(const QJsonObject &jsonRes);
    void H_RegisterAct(const QJsonObject &jsonRes);
    void H_UpdateAct(const QJsonObject &jsonRes);
    void H_LoadAct(const QJsonObject &jsonRes);
    void fetchAvatarImage(const QString &url, const QString &action);

private:
    QNetworkAccessManager *networkManager;

    void sendRequest(const QUrl &url, const QJsonObject &json, const QString &action);
    void handleResponse(QNetworkReply *reply, const QString &action);

};

#endif // FLASKINFO_H
