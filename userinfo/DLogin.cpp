#include "include/DLogin.h"
#include "ui/ui_DLogin.h"
#include <QMessageBox>
#include <QFileDialog>

DLogin::DLogin(DBMySQL *dbmysql, QWidget *parent)
    : QDialog(parent), ui(new Ui::DLogin), dbmysql(dbmysql)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    ui->loginBtn->setEnabled(false);
    ui->registerBtn->setEnabled(false);

    flaskinfo = new FlaskInfo(this);

    // Connect flaskinfo signals to the corresponding slots
    connect(flaskinfo, &FlaskInfo::loginResponseReceived, this, &DLogin::onLoginResponse);
    connect(flaskinfo, &FlaskInfo::registerResponseReceived, this, &DLogin::onRegisterResponse);
    connect(flaskinfo, &FlaskInfo::errorOccurred, this, &DLogin::onNetworkError);
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

DLogin::~DLogin() {
    delete ui;
}

void DLogin::on_loginBtn_clicked()
{
    QString usernameText = ui->username->text();
    QString passwordText = ui->password->text();

    if (usernameText.isEmpty() || passwordText.isEmpty()) {
        QMessageBox::warning(this, "警告", "用户名和密码不能为空");
        return;
    }

    flaskinfo->loginUser(usernameText, passwordText);
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

    flaskinfo->registerUser(usernameText, passwordText, avatarData);
}

void DLogin::onLoginResponse(const QJsonObject &response)
{
    QString message = response["message"].toString();
    if (message == "Login successful") {
        // Handle login success logic
        QString avatarBase64 = response["avatar"].toString();
        if (!avatarBase64.isEmpty()) {
            QByteArray avatarData = QByteArray::fromBase64(avatarBase64.toUtf8());
            QImage avatarImage;
            avatarImage.loadFromData(avatarData);
            ui->avatar_pushButton->setIcon(QIcon(QPixmap::fromImage(avatarImage)));
            emit loginSuccessful(response["username"].toString());

        }
        QMessageBox::information(this, "登录成功", message);
    } else {
        QMessageBox::warning(this, "登录失败", message);
    }
}

void DLogin::onRegisterResponse(const QJsonObject &response)
{
    QString message = response["message"].toString();
    if (message == "User registered successfully!") {
        QMessageBox::information(this, "注册成功", message);
    } else {
        QMessageBox::critical(this, "注册失败", message);
    }
}

void DLogin::onNetworkError(const QString &error)
{
    QMessageBox::warning(this, "网络错误", error);
}
