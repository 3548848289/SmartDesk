/********************************************************************************
** Form generated from reading UI file 'DInfo.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DINFO_H
#define UI_DINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DInfo
{
public:
    QLabel *avatarLabel;
    QLineEdit *nameEdit;
    QLineEdit *mottoEdit;
    QLineEdit *locationEdit;
    QLineEdit *companyEdit;
    QComboBox *genderCombo;
    QPushButton *saveButton;
    QDateEdit *birthdayEdit;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *accountEdit;
    QLabel *label_7;

    void setupUi(QDialog *DInfo)
    {
        if (DInfo->objectName().isEmpty())
            DInfo->setObjectName("DInfo");
        DInfo->resize(305, 300);
        avatarLabel = new QLabel(DInfo);
        avatarLabel->setObjectName("avatarLabel");
        avatarLabel->setGeometry(QRect(10, 10, 81, 81));
        avatarLabel->setStyleSheet(QString::fromUtf8("/*QLabel {\n"
"\n"
"    border: 1px solid #003366; \n"
"    border-radius: 25px; \n"
"    padding: 10px;  \n"
"    width: 50px; \n"
"    height: 50px;\n"
"    text-align: center; \n"
"}\n"
"*/"));
        nameEdit = new QLineEdit(DInfo);
        nameEdit->setObjectName("nameEdit");
        nameEdit->setGeometry(QRect(180, 20, 113, 23));
        mottoEdit = new QLineEdit(DInfo);
        mottoEdit->setObjectName("mottoEdit");
        mottoEdit->setGeometry(QRect(180, 50, 113, 23));
        locationEdit = new QLineEdit(DInfo);
        locationEdit->setObjectName("locationEdit");
        locationEdit->setGeometry(QRect(180, 180, 113, 23));
        companyEdit = new QLineEdit(DInfo);
        companyEdit->setObjectName("companyEdit");
        companyEdit->setGeometry(QRect(180, 220, 113, 23));
        genderCombo = new QComboBox(DInfo);
        genderCombo->addItem(QString());
        genderCombo->addItem(QString());
        genderCombo->addItem(QString());
        genderCombo->setObjectName("genderCombo");
        genderCombo->setGeometry(QRect(180, 90, 111, 24));
        saveButton = new QPushButton(DInfo);
        saveButton->setObjectName("saveButton");
        saveButton->setGeometry(QRect(180, 260, 111, 21));
        birthdayEdit = new QDateEdit(DInfo);
        birthdayEdit->setObjectName("birthdayEdit");
        birthdayEdit->setGeometry(QRect(180, 140, 110, 24));
        label = new QLabel(DInfo);
        label->setObjectName("label");
        label->setGeometry(QRect(120, 140, 61, 21));
        label_2 = new QLabel(DInfo);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(120, 220, 61, 21));
        label_3 = new QLabel(DInfo);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(120, 50, 61, 21));
        label_4 = new QLabel(DInfo);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(120, 180, 61, 21));
        label_5 = new QLabel(DInfo);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(120, 90, 61, 21));
        label_6 = new QLabel(DInfo);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(120, 20, 54, 16));
        accountEdit = new QLineEdit(DInfo);
        accountEdit->setObjectName("accountEdit");
        accountEdit->setGeometry(QRect(10, 140, 81, 23));
        accountEdit->setReadOnly(true);
        label_7 = new QLabel(DInfo);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 100, 91, 31));
        QWidget::setTabOrder(accountEdit, nameEdit);
        QWidget::setTabOrder(nameEdit, mottoEdit);
        QWidget::setTabOrder(mottoEdit, genderCombo);
        QWidget::setTabOrder(genderCombo, birthdayEdit);
        QWidget::setTabOrder(birthdayEdit, locationEdit);
        QWidget::setTabOrder(locationEdit, companyEdit);
        QWidget::setTabOrder(companyEdit, saveButton);

        retranslateUi(DInfo);

        QMetaObject::connectSlotsByName(DInfo);
    } // setupUi

    void retranslateUi(QDialog *DInfo)
    {
        DInfo->setWindowTitle(QCoreApplication::translate("DInfo", "Dialog", nullptr));
        avatarLabel->setText(QCoreApplication::translate("DInfo", "\345\244\264\345\203\217", nullptr));
        genderCombo->setItemText(0, QCoreApplication::translate("DInfo", "Male", nullptr));
        genderCombo->setItemText(1, QCoreApplication::translate("DInfo", "Female", nullptr));
        genderCombo->setItemText(2, QCoreApplication::translate("DInfo", "Other", nullptr));

        saveButton->setText(QCoreApplication::translate("DInfo", "\344\277\235\345\255\230", nullptr));
        label->setText(QCoreApplication::translate("DInfo", "\347\224\237\346\227\245", nullptr));
        label_2->setText(QCoreApplication::translate("DInfo", "\345\205\254\345\217\270", nullptr));
        label_3->setText(QCoreApplication::translate("DInfo", "\345\272\247\345\217\263\351\223\255", nullptr));
        label_4->setText(QCoreApplication::translate("DInfo", "\344\275\217\345\235\200", nullptr));
        label_5->setText(QCoreApplication::translate("DInfo", "\346\200\247\345\210\253", nullptr));
        label_6->setText(QCoreApplication::translate("DInfo", "\345\220\215\347\247\260", nullptr));
        accountEdit->setText(QString());
        label_7->setText(QCoreApplication::translate("DInfo", "\350\264\246\345\217\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DInfo: public Ui_DInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DINFO_H
