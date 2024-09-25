#include "DInfo.h"
#include "../ui/ui_DInfo.h"


DInfo::DInfo(const QString& username, DBMySQL* dmMysql, QWidget* parent) :
    QDialog(parent), username(username), dmMysql(dmMysql), ui(new Ui::DInfo) {

    QGridLayout* gridLayout = new QGridLayout(this);


    this->resize(400, 300);
    gridLayout->setObjectName("gridLayout");

    avatarLabel = new QLabel("头像",this);
    gridLayout->addWidget(avatarLabel, 0, 0, 2, 1);


    nameLabel = new QLabel("名字:", this);
    gridLayout->addWidget(nameLabel, 0, 1, 1, 1);
    nameEdit = new ElaLineEdit(this);
    gridLayout->addWidget(nameEdit, 0, 2, 1, 1);


    mottoLabel = new QLabel("座右铭:", this);
    gridLayout->addWidget(mottoLabel, 1, 1, 1, 1);
    mottoEdit = new ElaLineEdit(this);
    gridLayout->addWidget(mottoEdit, 1, 2, 1, 1);


    genderLabel = new QLabel("性别:", this);
    gridLayout->addWidget(genderLabel, 2, 1, 1, 1);
    genderCombo = new ElaComboBox(this);
    gridLayout->addWidget(genderCombo, 2, 2, 1, 1);
    genderCombo->addItems({"Male", "Female", "Other"});


    accountLabel = new QLabel("账号名:", this);
    gridLayout->addWidget(accountLabel, 2, 0, 1, 1);
    accountEdit = new ElaLineEdit(this);
    gridLayout->addWidget(accountEdit, 3, 0, 1, 1);

    birthdayLabel = new QLabel("生日:", this);
    gridLayout->addWidget(birthdayLabel, 3, 1, 1, 1);
    birthdayEdit = new QDateEdit(this);
    gridLayout->addWidget(birthdayEdit, 3, 2, 1, 1);


    locationLabel = new QLabel("住址:", this);
    gridLayout->addWidget(locationLabel, 4, 1, 1, 1);
    locationEdit = new ElaLineEdit(this);
    gridLayout->addWidget(locationEdit, 4, 2, 1, 1);


    companyLabel = new QLabel("公司名:", this);
    gridLayout->addWidget(companyLabel, 5, 1, 1, 1);
    companyEdit = new ElaLineEdit(this);
    gridLayout->addWidget(companyEdit, 5, 2, 1, 1);


    saveButton = new QPushButton("保存", this);
    gridLayout->addWidget(saveButton, 6, 2, 1, 1);
    connect(saveButton, &QPushButton::clicked, this, &DInfo::saveUserInfo);

    loadUserInfo();
}


void DInfo::loadUserInfo() {
    QMap<QString, QVariant> userInfo = dmMysql->getUserInfo(username);    
    accountEdit->setText(userInfo["username"].toString());
    QByteArray avatarData = userInfo["avatar"].toByteArray();
    if (!avatarData.isEmpty()) {
        QImage image;
        if (image.loadFromData(avatarData)) {
            avatarLabel->setPixmap(QPixmap::fromImage(image));
        } else {
            qDebug() << "Failed to load image from data.";
        }
    } else {
        qDebug() << "Avatar data is empty.";
    }
    nameEdit->setText(userInfo["name"].toString());
    mottoEdit->setText(userInfo["motto"].toString());
    genderCombo->setCurrentText(userInfo["gender"].toString());
    birthdayEdit->setDate(userInfo["birthday"].toDate());
    locationEdit->setText(userInfo["location"].toString());
    companyEdit->setText(userInfo["company"].toString());
}

void DInfo::saveUserInfo() {
    QMap<QString, QVariant> userInfo;
    userInfo["motto"] = mottoEdit->text();
    userInfo["gender"] = genderCombo->currentText();
    userInfo["birthday"] = birthdayEdit->date();
    userInfo["location"] = locationEdit->text();
    userInfo["company"] = companyEdit->text();

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
