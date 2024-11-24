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
    void loginUser(const QString &username, const QString &password);
    void registerUser(const QString &username, const QString &password, const QByteArray &avatarData);
    void updateUserInfo(const QString &username, const QMap<QString, QVariant> &userInfo);
    void loadUserInfo(const QString &username);

signals:
    void loginResponseReceived(const QJsonObject &response);
    void registerResponseReceived(const QJsonObject &response);
    void updateResponseReceived(const QJsonObject &response);
    void userInfoLoaded(const QJsonObject &userInfo);

    void errorOccurred(const QString &error);
    void avatarDownloaded(const QByteArray &data, const QString &action);

private slots:
    void onLoginResponse(QNetworkReply *reply);
    void fetchAvatarImage(const QString &avatarUrl, const QString &action);

    void onRegisterResponse(QNetworkReply *reply);
    void onUpdateResponse(QNetworkReply *reply);
    void onLoadUserInfoResponse(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkManager;

    void sendRequest(const QUrl &url, const QJsonObject &json, const QString &action);
};

#endif // FLASKINFO_H
