#include "DLogin.h"
#include "../ui/ui_DLogin.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QBuffer>

bool DLogin::loginUser(const QString &username, const QString &password, QString &statusMessage) {
    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (query.exec()) {
        if (query.next()) {
            QString dbPassword = query.value(0).toString();
            if (dbPassword == password) {
                statusMessage = "登录成功";
                return true;
            } else {
                statusMessage = "密码错误";
                return false;
            }
        } else {
            statusMessage = "用户不存在";
            return false;
        }
    } else {
        statusMessage = "数据库查询失败: " + query.lastError().text();
                                                    return false;
    }
}

bool DLogin::dbregisterUser(const QString &username, const QString &password, const QByteArray &avatarData, QString &statusMessage) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password, avatar) VALUES (:username, :password, :avatar)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":avatar", avatarData);

    if (query.exec()) {
        statusMessage = "注册成功";
        return true;
    } else {
        statusMessage = "注册失败: " + query.lastError().text();
                                           return false;
    }
}


DLogin::DLogin(QWidget *parent) : QDialog(parent), ui(new Ui::DLogin) {
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    ui->login_pushButton->setEnabled(false);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("qtdb");
    db.setUserName("root");
    db.setPassword("Mysql20039248");
    if (!db.open()) {
        QMessageBox::critical(this, "数据库错误", "无法连接到数据库: " + db.lastError().text());
        return;
    }
        \
}
DLogin::~DLogin() {
    delete ui;
}

void DLogin::on_radioButton_clicked() {
    if (ui->radioButton->isChecked()) {
        ui->login_pushButton->setStyleSheet("background-color: rgb(0, 141, 235);");
        ui->login_pushButton->setEnabled(true);
    } else {
        ui->login_pushButton->setStyleSheet("background-color: rgb(158, 218, 255);");
        ui->login_pushButton->setEnabled(false);
    }
}

void DLogin::on_login_pushButton_clicked() {
    QString username = ui->username->text();
    QString password = ui->password->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "警告", "用户名和密码不能为空");
        return;
    }

    QString statusMessage;
    if (loginUser(username, password, statusMessage)) {
        QMessageBox::information(this, "登录成功", statusMessage);
        ui->loginwidget->hide();
        ui->statusLabel->setText("登录成功");
    } else {
        QMessageBox::warning(this, "登录失败", statusMessage);
    }
}

void DLogin::registerUser(const QString &username, const QString &password) {
    if (avatarImage.isNull()) {
        QMessageBox::warning(this, "警告", "请先上传头像");
        return;
    }

    QByteArray avatarData;
    QBuffer buffer(&avatarData);
    avatarImage.save(&buffer, "PNG");

    QString statusMessage;
    if (dbregisterUser(username, password, avatarData, statusMessage)) {
        QMessageBox::information(this, "注册成功", statusMessage);
        ui->loginwidget->hide();
        ui->statusLabel->clear();
        ui->avatar_pushButton->setIcon(QIcon(avatarImage));
        ui->statusLabel->setText("登录成功");
    } else {
        QMessageBox::critical(this, "注册失败", statusMessage);
    }
}

void DLogin::on_exit_toolButton_clicked() {
//    QMessageBox::StandardButton reply;
//    reply = QMessageBox::question(this, "退出", "你确定要退出登录吗?", QMessageBox::Yes | QMessageBox::No);
//    if (reply == QMessageBox::Yes)
    {
        ui->username->clear();
        ui->password->clear();
        ui->avatar_pushButton->setIcon(QIcon());
        ui->statusLabel->clear();
        close();
    }
}

void DLogin::on_avatar_pushButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "选择头像", "", "Images (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty()) {
        QPixmap avatar(fileName);
        avatarImage = avatar;
        if (!avatar.isNull()) {
            QSize buttonSize = ui->avatar_pushButton->size();
            QSize scaledSize = buttonSize * 0.6;
            QPixmap scaledPixmap = avatar.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

            ui->avatar_pushButton->setIcon(QIcon(avatar));
            ui->avatar_pushButton->setIconSize(ui->avatar_pushButton->size());
        } else {
            qWarning("无法加载图像: %s", qPrintable(fileName));
        }
    }
}
