#include "include/FlaskInfo.h"

FlaskInfo::FlaskInfo(QObject *parent) : QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
}

void FlaskInfo::loginUser(const QString &username, const QString &password)
{
    QJsonObject json;
    json["username"] = username;
    json["password"] = password;

    sendRequest(QUrl("http://127.0.0.1:5000/login"), json, "login");
}

void FlaskInfo::registerUser(const QString &username, const QString &password, const QByteArray &avatarData)
{
    QJsonObject json;
    json["username"] = username;
    json["password"] = password;
    json["avatar"] = QString(avatarData.toBase64());

    sendRequest(QUrl("http://127.0.0.1:5000/register"), json, "register");
}

void FlaskInfo::loadUserInfo(const QString &username)
{
    QJsonObject json;
    json["username"] = username; // 传递用户名作为查询参数

    sendRequest(QUrl("http://127.0.0.1:5000/get_user_info"), json, "load_user_info");
}

void FlaskInfo::updateUserInfo(const QString &username, const QMap<QString, QVariant> &userInfo)
{
    QJsonObject json;
    json["username"] = username;
    json["name"] = userInfo["name"].toString();
    json["motto"] = userInfo["motto"].toString();
    json["gender"] = userInfo["gender"].toString();
    json["birthday"] = userInfo["birthday"].toDate().toString("yyyy-MM-dd");
    json["location"] = userInfo["location"].toString();
    json["company"] = userInfo["company"].toString();

    sendRequest(QUrl("http://127.0.0.1:5000/update_user_info"), json, "update_user_info");
}

void FlaskInfo::sendRequest(const QUrl &url, const QJsonObject &json, const QString &action)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    QNetworkReply *reply = networkManager->post(request, data);
    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (action == "login") {
            onLoginResponse(reply);
        } else if (action == "register") {
            onRegisterResponse(reply);
        } else if (action == "update_user_info") {
            onUpdateResponse(reply);
        } else if (action == "load_user_info") {
            onLoadUserInfoResponse(reply);
        }
    });
}

void FlaskInfo::onLoginResponse(QNetworkReply *reply)
{

    if (reply->error() != QNetworkReply::NoError) {
        emit errorOccurred(reply->errorString());
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonResponse = jsonDoc.object();

    qDebug() << "Response JSON:" << jsonResponse;
    if (jsonResponse.contains("avatar_url") && !jsonResponse["avatar_url"].toString().isEmpty()) {

        QString baseUrl = "http://127.0.0.1:5000";  // 假设服务器地址
        QString avatarUrl = baseUrl + jsonResponse["avatar_url"].toString();  // 拼接完整的 URL
        qDebug() << "Full Avatar URL:" << avatarUrl;
        fetchAvatarImage(avatarUrl, "login_avatar");

    } else {
        qDebug() << "avatar_url not found or is empty!";
    }

    emit loginResponseReceived(jsonResponse);
    reply->deleteLater();
}

void FlaskInfo::fetchAvatarImage(const QString &url, const QString &action)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, action]() {
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << "Failed to download avatar:" << reply->errorString();
            emit avatarDownloaded(QByteArray(), action);  // 失败时传递空数据
        } else {
            QByteArray imageData = reply->readAll();
            emit avatarDownloaded(imageData, action);  // 成功时传递图像数据
        }
        reply->deleteLater();
    });
}


void FlaskInfo::onRegisterResponse(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        emit errorOccurred(reply->errorString());
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    emit registerResponseReceived(jsonDoc.object());

    reply->deleteLater();
}

void FlaskInfo::onUpdateResponse(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        emit errorOccurred(reply->errorString());
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);

    QJsonObject jsonResponse = jsonDoc.object();

    if (jsonResponse.contains("success") && jsonResponse["success"].toBool()) {
        emit updateResponseReceived(jsonResponse);
    }
    reply->deleteLater();
}

void FlaskInfo::onLoadUserInfoResponse(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        emit errorOccurred(reply->errorString());
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    if (!jsonDoc.isObject()) {
        emit errorOccurred("Invalid JSON response.");
        reply->deleteLater();
        return;
    }

    QJsonObject userInfo = jsonDoc.object();

    if (userInfo.contains("avatar_url") && !userInfo["avatar_url"].toString().isEmpty()) {
        QString avatarUrl = userInfo["avatar_url"].toString();
        fetchAvatarImage(avatarUrl, "load_user_avatar");
    }

    emit userInfoLoaded(userInfo);
    reply->deleteLater();
}
