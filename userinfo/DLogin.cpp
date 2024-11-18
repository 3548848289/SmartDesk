#include "include/DLogin.h"
#include "ui/ui_DLogin.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QBuffer>

DLogin::DLogin(DBMySQL *dbmysql, QWidget *parent)
    : QDialog(parent), ui(new Ui::DLogin), dbmysql(dbmysql) {
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    ui->loginBtn->setEnabled(false);
    ui->registerBtn->setEnabled(false);
    networkManager = new QNetworkAccessManager(this);
}

DLogin::~DLogin() {
    delete ui;
}


void DLogin::on_radioButton_clicked() {
    if (ui->radioButton->isChecked()) {
        ui->loginBtn->setStyleSheet("background-color: rgb(0, 141, 235);");
        ui->loginBtn->setEnabled(true);
        ui->registerBtn->setStyleSheet("background-color: rgb(0, 141, 235);");
        ui->registerBtn->setEnabled(true);
    } else {
        ui->loginBtn->setStyleSheet("background-color: rgb(158, 218, 255);");
        ui->loginBtn->setEnabled(false);
        ui->registerBtn->setStyleSheet("background-color: rgb(158, 218, 255);");
        ui->registerBtn->setEnabled(false);
    }
}



void DLogin::on_loginBtn_clicked()
{
    QString usernameText = ui->username->text();
    QString passwordText = ui->password->text();

    if (usernameText.isEmpty() || passwordText.isEmpty()) {
        QMessageBox::warning(this, "警告", "用户名和密码不能为空");
        return;
    }

    // 创建 JSON 请求数据
    QJsonObject json;
    json["username"] = usernameText;
    json["password"] = passwordText;

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    // 创建请求
    QNetworkRequest request(QUrl("http://127.0.0.1:5000/login"));  // 请确保 Flask 后端在此地址运行
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 发送请求
    QNetworkReply *reply = networkManager->post(request, data);

    // 连接信号槽，处理请求响应
    connect(reply, &QNetworkReply::finished, this, &DLogin::onLoginResponse);
}

void DLogin::onLoginResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (reply->error() != QNetworkReply::NoError) {
        // 获取详细的错误信息
        qDebug() << "Network Error: " << reply->errorString();

        // 如果是 HTTP 错误码，可以进一步了解错误原因
        int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "HTTP Status Code: " << httpStatusCode;

        // 提示框显示错误
        QMessageBox::warning(this, "错误", "无法连接到服务器: " + reply->errorString());
        reply->deleteLater();
        return;
    }


    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObject = jsonDoc.object();

    QString message = jsonObject["message"].toString();

    if (message == "Login successful") {
        QByteArray avatarData = QByteArray::fromBase64(jsonObject["avatar"].toString().toUtf8());
        avatarImage.loadFromData(avatarData);

        QMessageBox::information(this, "登录成功", message);
        ui->loginwidget->hide();
        ui->avatar_pushButton->setIcon(QIcon(avatarImage));
        ui->avatar_pushButton->setIconSize(ui->avatar_pushButton->size());
        ui->statusLabel->setText("登录成功");
        emit loginSuccessful(ui->username->text());
        close();
    } else {
        QMessageBox::warning(this, "登录失败", message);
    }

    reply->deleteLater();
}


void DLogin::on_registerBtn_clicked()
{
    QString usernameText = ui->username->text();
    QString passwordText = ui->password->text();

    if (avatarImage.isNull()) {
        QMessageBox::warning(this, "警告", "请先上传头像");
        return;
    }

    QByteArray avatarData;
    QBuffer buffer(&avatarData);
    avatarImage.save(&buffer, "PNG");

    // 创建 JSON 请求数据
    QJsonObject json;
    json["username"] = usernameText;
    json["password"] = passwordText;
    json["avatar"] = QString(avatarData.toBase64());

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();
    qDebug() << "DLogin::on_login_pushButton_clicked" << data;

    // 创建请求
    QNetworkRequest request(QUrl("http://127.0.0.1:5000/register"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 发送请求
    QNetworkReply *reply = networkManager->post(request, data);

    // 连接信号槽，处理请求响应
    connect(reply, &QNetworkReply::finished, this, &DLogin::onRegisterResponse);
}

void DLogin::registerUser(const QString &username, const QString &password) {

}

void DLogin::onRegisterResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) {
        QMessageBox::warning(this, "错误", "响应来自未知源");
        return;
    }

    if (reply->error() != QNetworkReply::NoError) {
        // 获取详细的错误信息
        qDebug() << "Network Error: " << reply->errorString();

        // 如果是 HTTP 错误码，可以进一步了解错误原因
        int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "HTTP Status Code: " << httpStatusCode;

        // 提示框显示错误
        QMessageBox::warning(this, "错误", "无法连接到服务器: " + reply->errorString());
        reply->deleteLater();
        return;
    }


    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObject = jsonDoc.object();

    QString statusMessage = jsonObject["message"].toString();

    if (statusMessage == "User registered successfully!") {
        QMessageBox::information(this, "注册成功", statusMessage);
        ui->loginwidget->hide();
        ui->avatar_pushButton->setIcon(QIcon(avatarImage));
        ui->statusLabel->setText("登录成功");
        emit loginSuccessful(ui->username->text());
    } else {
        QMessageBox::critical(this, "注册失败", statusMessage);
    }

    reply->deleteLater();
}


void DLogin::on_exit_toolButton_clicked() {
    ui->username->clear();
    ui->password->clear();
    ui->avatar_pushButton->setIcon(QIcon());
    ui->statusLabel->clear();
    close();
}

void DLogin::on_avatar_pushButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "选择头像", "", "Images (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty()) {
        QPixmap avatar(fileName);
        avatarImage = avatar;
        if (!avatar.isNull()) {
            ui->avatar_pushButton->setIcon(QIcon(avatar));
            ui->avatar_pushButton->setIconSize(ui->avatar_pushButton->size());
        } else {
            qWarning("无法加载图像: %s", qPrintable(fileName));
        }
    }
}



//void DLogin::on_login_pushButton_clicked() {
//    QString usernameText = ui->username->text(); // 使用username指针获取文本
//    QString passwordText = ui->password->text(); // 获取密码文本

//    if (usernameText.isEmpty() || passwordText.isEmpty()) {
//        QMessageBox::warning(this, "警告", "用户名和密码不能为空");
//        return;
//    }

//    QByteArray avatarData;
//    QString statusMessage;
//    if (dbmysql->loginUser(usernameText, passwordText, avatarData, statusMessage)) {
//        avatarImage.loadFromData(avatarData);
//        QMessageBox::information(this, "登录成功", statusMessage);
//        ui->loginwidget->hide();
//        ui->avatar_pushButton->setIcon(QIcon(avatarImage));
//        ui->avatar_pushButton->setIconSize(ui->avatar_pushButton->size());
//        ui->statusLabel->setText("登录成功");
//        emit loginSuccessful(usernameText);
//        close();
//    } else {
//        registerUser(usernameText, passwordText);
//        //QMessageBox::warning(this, "登录失败", statusMessage);
//    }
//}
//void DLogin::registerUser(const QString &username, const QString &password) {
//    if (avatarImage.isNull()) {
//        QMessageBox::warning(this, "警告", "请先上传头像");
//        return;
//    }

//    QByteArray avatarData;
//    QBuffer buffer(&avatarData);
//    avatarImage.save(&buffer, "PNG");

//    QString statusMessage;
//    if (dbmysql->registerUser(username, password, avatarData, statusMessage)) {
//        QMessageBox::information(this, "注册成功", statusMessage);
//        ui->loginwidget->hide();
//        ui->statusLabel->clear();
//        ui->avatar_pushButton->setIcon(QIcon(avatarImage));
//        ui->statusLabel->setText("登录成功");
//        emit loginSuccessful(username);

//    } else {
//        QMessageBox::critical(this, "注册失败", statusMessage);
//    }
//}


