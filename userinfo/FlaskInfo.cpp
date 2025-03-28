#include "include/FlaskInfo.h"

FlaskInfo::FlaskInfo(QObject *parent) : QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
}

void FlaskInfo::route_loginUser(const QString &username, const QString &password)
{
    QJsonObject json;
    json["username"] = username;
    json["password"] = password;

    sendRequest(QUrl("http://127.0.0.1:5000/user/login"), json, "login");
}

void FlaskInfo::route_registerUser(const QString &username, const QString &password, const QByteArray &avatarData)
{
    QJsonObject json;
    json["username"] = username;
    json["password"] = password;
    json["avatar"] = QString(avatarData.toBase64());

    sendRequest(QUrl("http://127.0.0.1:5000/user/register"), json, "register");
}

void FlaskInfo::route_loadUserInfo(const QString &username)
{
    QJsonObject json;
    json["username"] = username; // 传递用户名作为查询参数

    sendRequest(QUrl("http://127.0.0.1:5000/info/get_user_info"), json, "load_user_info");
}

void FlaskInfo::route_updateUserInfo(const QString &username, const QMap<QString, QVariant> &userInfo)
{
    QJsonObject json;
    json["username"] = username;
    json["name"] = userInfo["name"].toString();
    json["motto"] = userInfo["motto"].toString();
    json["gender"] = userInfo["gender"].toString();
    json["birthday"] = userInfo["birthday"].toDate().toString("yyyy-MM-dd");
    json["location"] = userInfo["location"].toString();
    json["company"] = userInfo["company"].toString();

    sendRequest(QUrl("http://127.0.0.1:5000/info/update_user_info"), json, "update_user_info");
}


void FlaskInfo::sendRequest(const QUrl &url, const QJsonObject &json, const QString &action)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray data = QJsonDocument(json).toJson();
    QNetworkReply *reply = networkManager->post(request, data);

    connect(reply, &QNetworkReply::finished, this, [this, reply, action]() {
        handleResponse(reply, action);
    });
}

void FlaskInfo::handleResponse(QNetworkReply *reply, const QString &action)
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

    QJsonObject jsonRes = jsonDoc.object();
    qDebug() << "Response JSON:" << jsonRes;

    // 根据不同的动作处理
    if (action == "login") {
        H_LoginAct(jsonRes);
    } else if (action == "register") {
        H_RegisterAct(jsonRes);
    } else if (action == "update_user_info") {
        H_UpdateAct(jsonRes);
    } else if (action == "load_user_info") {
        H_LoadAct(jsonRes);
    }

    reply->deleteLater();
}

void FlaskInfo::H_LoginAct(const QJsonObject &jsonRes)
{
    if (jsonRes.contains("avatar_url") && !jsonRes["avatar_url"].toString().isEmpty()) {
        QString baseUrl = "http://127.0.0.1:5000";
        QString avatarUrl = baseUrl + jsonRes["avatar_url"].toString();
        qDebug() << "Full Avatar URL:" << avatarUrl;
        fetchAvatarImage(avatarUrl, "login_avatar");
    } else {
        qDebug() << "avatar_url not found or is empty!";
    }
    emit s_loginRec(jsonRes);
}

void FlaskInfo::H_RegisterAct(const QJsonObject &jsonRes)
{
    emit s_registerRec(jsonRes); // 改为简化后的信号名称
}

void FlaskInfo::H_UpdateAct(const QJsonObject &jsonRes)
{
    if (jsonRes.contains("success") && jsonRes["success"].toBool()) {
        emit s_updateRec(jsonRes);
    } else {
        emit errorOccurred("Update failed.");
    }
}

void FlaskInfo::H_LoadAct(const QJsonObject &jsonRes)
{
    if (jsonRes.contains("avatar_url") && !jsonRes["avatar_url"].toString().isEmpty()) {
        fetchAvatarImage(jsonRes["avatar_url"].toString(), "load_user_avatar");
    }
    emit s_loadRec(jsonRes);
}

void FlaskInfo::fetchAvatarImage(const QString &url, const QString &action)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply, action]() {
        QByteArray imageData;
        if (reply->error() == QNetworkReply::NoError) {
            imageData = reply->readAll();
        } else {
            qDebug() << "Failed to download avatar:" << reply->errorString();
        }
        emit avatarDownloaded(imageData, action);
        reply->deleteLater();
    });
}
