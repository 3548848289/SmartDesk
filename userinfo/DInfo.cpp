#include "ui/ui_DInfo.h"
#include "include/DInfo.h"
#include <QMessageBox>

DInfo::DInfo(const QString& username, QWidget* parent) :
    QDialog(parent), username(username), ui(new Ui::DInfo)
{
    ui->setupUi(this);
    flaskinfo = new FlaskInfo(this);
    qDebug() << username;    
    flaskinfo->route_loadUserInfo(username);

    connect(flaskinfo, &FlaskInfo::s_loadRec, this, &DInfo::loadUserInfo);  // 使用 flaskinfo 对象
}

DInfo::~DInfo()
{
    delete ui;
    delete flaskinfo;
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
    QString avatarBase64 = userInfo["avator_base64"].toString();  // 获取 Base64 字符串
    QByteArray avatarData = QByteArray::fromBase64(avatarBase64.toUtf8());  // 将 Base64 字符串转换为字节数组
    if (!avatarData.isEmpty()) {
        QImage image;
        if (image.loadFromData(avatarData)) {
            storedAvatar = QPixmap::fromImage(image);
            qDebug() << "成功缓存图片";
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


void DInfo::onUserInfoUpdated(const QJsonObject &response) {
    if (response.isEmpty()) {
        QMessageBox::warning(this, "错误", "更新失败，请重试");
        return;
    }

    QMessageBox::information(this, "成功", "用户信息更新成功！");
    this->close();
}

void DInfo::onErrorOccurred(const QString &error) {
    QMessageBox::warning(this, "错误", error);
}

void DInfo::on_saveButton_clicked()
{
    QMap<QString, QVariant> userInfo;

    userInfo["username"] = ui->accountEdit->text();
    userInfo["name"] = ui->nameEdit->text();
    userInfo["motto"] = ui->mottoEdit->text();
    userInfo["gender"] = ui->genderCombo->currentText();
    userInfo["birthday"] = ui->birthdayEdit->date();
    userInfo["location"] = ui->locationEdit->text();
    userInfo["company"] = ui->companyEdit->text();

    // 创建 FlaskInfo 对象并连接信号槽
    FlaskInfo *flaskInfo = new FlaskInfo(this);
    connect(flaskInfo, &FlaskInfo::s_updateRec, this, &DInfo::onUserInfoUpdated);
    connect(flaskInfo, &FlaskInfo::errorOccurred, this, &DInfo::onErrorOccurred);

    // 发送更新请求
    flaskInfo->route_updateUserInfo(username, userInfo);
}

