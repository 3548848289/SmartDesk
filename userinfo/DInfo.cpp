#include "include/DInfo.h"
#include "ui/ui_DInfo.h"


DInfo::DInfo(const QString& username, DBMySQL* dmMysql, QWidget* parent) :
    QDialog(parent), username(username), dmMysql(dmMysql), ui(new Ui::DInfo) {

    ui->setupUi(this);
    ui->genderCombo->addItems({"Male", "Female", "Other"});


    connect(ui->saveButton, &QPushButton::clicked, this, &DInfo::saveUserInfo);

    loadUserInfo();
}


void DInfo::loadUserInfo() {

    QMap<QString, QVariant> userInfo = dmMysql->getUserInfo(username);
    ui->accountEdit->setText(userInfo["username"].toString());

    QByteArray avatarData = userInfo["avatar"].toByteArray();
    if (!avatarData.isEmpty()) {
        QImage image;
        if (image.loadFromData(avatarData)) {
            storedAvatar = QPixmap::fromImage(image);
            ui->avatarLabel->setPixmap(storedAvatar);
        } else {
            qDebug() << "Failed to load image from data.";
        }
    } else {
        qDebug() << "Avatar data is empty.";
    }

    ui->avatarLabel->setPixmap(storedAvatar);
    ui->avatarLabel->setScaledContents(true);
    ui->nameEdit->setText(userInfo["name"].toString());
    ui->mottoEdit->setText(userInfo["motto"].toString());
    ui->genderCombo->setCurrentText(userInfo["gender"].toString());
    ui->birthdayEdit->setDate(userInfo["birthday"].toDate());
    ui->locationEdit->setText(userInfo["location"].toString());
    ui->companyEdit->setText(userInfo["company"].toString());
}

void DInfo::saveUserInfo() {
    QMap<QString, QVariant> userInfo;
    userInfo["name"] = ui->nameEdit->text();
    userInfo["motto"] = ui->mottoEdit->text();
    userInfo["gender"] = ui->genderCombo->currentText();
    userInfo["birthday"] = ui->birthdayEdit->date();
    userInfo["location"] = ui->locationEdit->text();
    userInfo["company"] = ui->companyEdit->text();

    if (dmMysql->insertUserInfo(username, userInfo)) {
        accept(); // Close dialog on successful save
    } else {
        QMessageBox::warning(this, "Error", "Failed to save user information.");
    }
}

DInfo::~DInfo()
{
    delete ui;
}

QPixmap DInfo::getStoredAvatar() const
{
    return storedAvatar;
}

