#include "DLogin.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QBuffer>

DLogin::DLogin(DBMySQL *dbInstance, QWidget *parent)
    : QDialog(parent),  db(dbInstance) {

    QVBoxLayout *verticalLayout = new QVBoxLayout(this);


        // 状态标签和退出按钮
        horizontalLayout_1 = new QHBoxLayout();
        statusLabel = new QLabel("状态", this);
        exit_toolButton = new QToolButton(this);
        exit_toolButton->setText("退出");
        horizontalLayout_1->addWidget(statusLabel);
        horizontalLayout_1->addWidget(exit_toolButton);
        verticalLayout->addLayout(horizontalLayout_1);

        // 头像按钮
        horizontalLayout_2 = new QHBoxLayout();
        avatar_pushButton = new ElaPushButton(this);
        avatar_pushButton->setFixedSize(100, 100);
        avatar_pushButton->setText("头像");
        horizontalLayout_2->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
        horizontalLayout_2->addWidget(avatar_pushButton);
        horizontalLayout_2->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
        verticalLayout->addLayout(horizontalLayout_2);

        // 登录表单
        loginwidget = new QWidget(this);
        horizontalLayout_3 = new QVBoxLayout(loginwidget);
        username = new ElaLineEdit(this);
        username->setPlaceholderText("用户名");
        username->setMinimumSize(200, 40); // 设置最小尺寸

        password = new ElaLineEdit(this);
        password->setPlaceholderText("密码");
        password->setEchoMode(QLineEdit::Password);
        password->setMinimumSize(200, 40); // 设置最小尺寸

        radioButton = new ElaRadioButton("记住我", this);
        login_pushButton = new ElaPushButton("登录", this);
        login_pushButton->setMinimumSize(200, 40); // 设置最小尺寸

        horizontalLayout_3->addWidget(username);
        horizontalLayout_3->addWidget(password);
        horizontalLayout_3->addWidget(radioButton);
        horizontalLayout_3->addWidget(login_pushButton);
        verticalLayout->addWidget(loginwidget);

        // 注册和忘记密码按钮
        horizontalLayout_4 = new QHBoxLayout();
        resiger_pushButton = new ElaPushButton("注册", this);
        line = new QFrame(this);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        forget_pushButton = new ElaPushButton("忘记密码", this);

        horizontalLayout_4->addWidget(resiger_pushButton);
        horizontalLayout_4->addWidget(line);
        horizontalLayout_4->addWidget(forget_pushButton);
        verticalLayout->addLayout(horizontalLayout_4);

    connect(radioButton, &QRadioButton::clicked, this, &DLogin::on_radioButton_clicked);
    connect(login_pushButton, &QPushButton::clicked, this, &DLogin::on_login_pushButton_clicked);
    connect(exit_toolButton, &QToolButton::clicked, this, &DLogin::on_exit_toolButton_clicked);
    connect(avatar_pushButton, &QPushButton::clicked, this, &DLogin::on_avatar_pushButton_clicked);


    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    login_pushButton->setEnabled(false);
}

DLogin::~DLogin() {
}

void DLogin::on_radioButton_clicked() {
    if (radioButton->isChecked()) {
        login_pushButton->setStyleSheet("background-color: rgb(0, 141, 235);");
        login_pushButton->setEnabled(true);
    } else {
        login_pushButton->setStyleSheet("background-color: rgb(158, 218, 255);");
        login_pushButton->setEnabled(false);
    }
}

void DLogin::on_login_pushButton_clicked() {
    QString usernameText = username->text(); // 使用username指针获取文本
    QString passwordText = password->text(); // 获取密码文本

    if (usernameText.isEmpty() || passwordText.isEmpty()) {
        QMessageBox::warning(this, "警告", "用户名和密码不能为空");
        return;
    }

    QByteArray avatarData;
    QString statusMessage;
    if (db->loginUser(usernameText, passwordText, avatarData, statusMessage)) {
        avatarImage.loadFromData(avatarData);
        QMessageBox::information(this, "登录成功", statusMessage);
        loginwidget->hide();
        avatar_pushButton->setIcon(QIcon(avatarImage));
        avatar_pushButton->setIconSize(avatar_pushButton->size());
        statusLabel->setText("登录成功");
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
        loginwidget->hide();
        statusLabel->clear();
        avatar_pushButton->setIcon(QIcon(avatarImage));
        statusLabel->setText("登录成功");
        emit loginSuccessful(username);

    } else {
        QMessageBox::critical(this, "注册失败", statusMessage);
    }
}

void DLogin::on_exit_toolButton_clicked() {
    username->clear();
    password->clear();
    avatar_pushButton->setIcon(QIcon());
    statusLabel->clear();
    close();
}

void DLogin::on_avatar_pushButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "选择头像", "", "Images (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty()) {
        QPixmap avatar(fileName);
        avatarImage = avatar;
        if (!avatar.isNull()) {
            avatar_pushButton->setIcon(QIcon(avatar));
            avatar_pushButton->setIconSize(avatar_pushButton->size());
        } else {
            qWarning("无法加载图像: %s", qPrintable(fileName));
        }
    }
}
