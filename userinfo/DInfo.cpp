#include "ui/ui_DInfo.h"
#include "include/DInfo.h"
#include <QMessageBox>

DInfo::DInfo(const QString& username, DBMySQL* dmMysql, QWidget* parent) :
    QDialog(parent), username(username), dmMysql(dmMysql), ui(new Ui::DInfo)
{
    ui->setupUi(this);
    ui->genderCombo->addItems({"Male", "Female", "Other"});

    // 创建 FlaskInfo 对象
    flaskinfo = new FlaskInfo(this);  // 这里实例化 flaskinfo
    qDebug() << username;
    flaskinfo->loadUserInfo(username);
    // 连接信号和槽
    connect(ui->saveButton, &QPushButton::clicked, this, &DInfo::saveUserInfo);
    connect(flaskinfo, &FlaskInfo::userInfoLoaded, this, &DInfo::loadUserInfo);  // 使用 flaskinfo 对象
}

DInfo::~DInfo()
{
    delete ui;
    delete flaskinfo;  // 记得在析构函数中删除 flaskinfo 对象
}

QPixmap DInfo::getStoredAvatar() const
{
    return storedAvatar;
}


void DInfo::loadUserInfo(const QJsonObject &userInfo) {
    if (userInfo.isEmpty()) {
        qWarning() << "Received empty user info!";
        return;
    }

    // 填充 UI 控件
    ui->accountEdit->setText(userInfo["username"].toString());
    ui->nameEdit->setText(userInfo["name"].toString());
    ui->mottoEdit->setText(userInfo["motto"].toString());
    ui->genderCombo->setCurrentText(userInfo["gender"].toString());

    // 处理日期字段
    QString birthdayStr = userInfo["birthday"].toString();  // 获取生日的字符串
    QDate birthday = QDate::fromString(birthdayStr, Qt::ISODate);  // 使用 ISO 格式解析日期
    if (birthday.isValid()) {
        ui->birthdayEdit->setDate(birthday);
    } else {
        qWarning() << "Invalid date format for birthday:" << birthdayStr;
    }

    ui->locationEdit->setText(userInfo["location"].toString());
    ui->companyEdit->setText(userInfo["company"].toString());

    // 处理头像
    QString avatarBase64 = userInfo["avatar"].toString();  // 获取 Base64 字符串
    QByteArray avatarData = QByteArray::fromBase64(avatarBase64.toUtf8());  // 将 Base64 字符串转换为字节数组
    if (!avatarData.isEmpty()) {
        QImage image;
        if (image.loadFromData(avatarData)) {
            storedAvatar = QPixmap::fromImage(image);
            ui->avatarLabel->setPixmap(storedAvatar);
        } else {
            qWarning() << "Failed to load image from data.";
        }
    } else {
        qDebug() << "Avatar data is empty.";
        ui->avatarLabel->clear(); // 清除头像
    }

    ui->avatarLabel->setPixmap(storedAvatar);
    ui->avatarLabel->setScaledContents(true);
}

void DInfo::saveUserInfo() {
    QMap<QString, QVariant> userInfo;
    userInfo["name"] = ui->nameEdit->text();
    userInfo["motto"] = ui->mottoEdit->text();
    userInfo["gender"] = ui->genderCombo->currentText();
    userInfo["birthday"] = ui->birthdayEdit->date();
    userInfo["location"] = ui->locationEdit->text();
    userInfo["company"] = ui->companyEdit->text();

    // 创建 FlaskInfo 对象并连接信号槽
    FlaskInfo *flaskInfo = new FlaskInfo(this);
    connect(flaskInfo, &FlaskInfo::updateResponseReceived, this, &DInfo::onUserInfoUpdated);
    connect(flaskInfo, &FlaskInfo::errorOccurred, this, &DInfo::onErrorOccurred);

    // 发送更新请求
    flaskInfo->updateUserInfo(username, userInfo);
}

void DInfo::onUserInfoUpdated(const QJsonObject &response) {
    if (response.isEmpty()) {
        QMessageBox::warning(this, "Error", "No data received from the server.");
        return;
    }

    // 更新成功后，显示提示框
    QMessageBox::information(this, "Success", "User information updated successfully!");

    // 根据需要，你也可以在这里刷新 UI 或做其他处理
}

void DInfo::onErrorOccurred(const QString &error) {
    // 错误处理：弹出警告框
    QMessageBox::warning(this, "Error", error);
}
