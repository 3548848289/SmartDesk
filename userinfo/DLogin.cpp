#include "DLogin.h"
#include "../ui/ui_DLogin.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QBuffer>

DLogin::DLogin(DBMySQL *dbInstance, QWidget *parent)
    : QDialog(parent), ui(new Ui::DLogin), db(dbInstance) {
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    ui->login_pushButton->setEnabled(false);
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
    QString usernameText = ui->username->text(); // 使用username指针获取文本
    QString passwordText = ui->password->text(); // 获取密码文本

    if (usernameText.isEmpty() || passwordText.isEmpty()) {
        QMessageBox::warning(this, "警告", "用户名和密码不能为空");
        return;
    }

    QByteArray avatarData;
    QString statusMessage;
    if (db->loginUser(usernameText, passwordText, avatarData, statusMessage)) {
        avatarImage.loadFromData(avatarData);
        QMessageBox::information(this, "登录成功", statusMessage);
        ui->loginwidget->hide();
        ui->avatar_pushButton->setIcon(QIcon(avatarImage));
        ui->avatar_pushButton->setIconSize(ui->avatar_pushButton->size());
        ui->statusLabel->setText("登录成功");
        emit loginSuccessful(usernameText);
        close();
    } else {
        registerUser(usernameText, passwordText);
//        QMessageBox::warning(this, "登录失败", statusMessage);
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
    if (db->registerUser(username, password, avatarData, statusMessage)) {
        QMessageBox::information(this, "注册成功", statusMessage);
        ui->loginwidget->hide();
        ui->statusLabel->clear();
        ui->avatar_pushButton->setIcon(QIcon(avatarImage));
        ui->statusLabel->setText("登录成功");
        emit loginSuccessful(username);

    } else {
        QMessageBox::critical(this, "注册失败", statusMessage);
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
