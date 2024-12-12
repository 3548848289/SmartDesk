/********************************************************************************
** Form generated from reading UI file 'FileRestoreWid.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILERESTOREWID_H
#define UI_FILERESTOREWID_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FileRestoreWid
{
public:
    QDateTimeEdit *dateTimeEdit;
    QLineEdit *lineEdit;
    QPushButton *dlBtn;
    QLabel *label;
    QPushButton *fastDlBtn;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QPushButton *dlBtn_2;

    void setupUi(QDialog *FileRestoreWid)
    {
        if (FileRestoreWid->objectName().isEmpty())
            FileRestoreWid->setObjectName("FileRestoreWid");
        FileRestoreWid->resize(400, 300);
        dateTimeEdit = new QDateTimeEdit(FileRestoreWid);
        dateTimeEdit->setObjectName("dateTimeEdit");
        dateTimeEdit->setGeometry(QRect(100, 90, 141, 41));
        lineEdit = new QLineEdit(FileRestoreWid);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(20, 20, 361, 41));
        dlBtn = new QPushButton(FileRestoreWid);
        dlBtn->setObjectName("dlBtn");
        dlBtn->setGeometry(QRect(290, 250, 91, 41));
        label = new QLabel(FileRestoreWid);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 90, 71, 41));
        fastDlBtn = new QPushButton(FileRestoreWid);
        fastDlBtn->setObjectName("fastDlBtn");
        fastDlBtn->setGeometry(QRect(10, 250, 91, 41));
        lineEdit_2 = new QLineEdit(FileRestoreWid);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(100, 160, 121, 41));
        label_2 = new QLabel(FileRestoreWid);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 160, 71, 41));
        dlBtn_2 = new QPushButton(FileRestoreWid);
        dlBtn_2->setObjectName("dlBtn_2");
        dlBtn_2->setGeometry(QRect(270, 160, 91, 41));

        retranslateUi(FileRestoreWid);

        QMetaObject::connectSlotsByName(FileRestoreWid);
    } // setupUi

    void retranslateUi(QDialog *FileRestoreWid)
    {
        FileRestoreWid->setWindowTitle(QCoreApplication::translate("FileRestoreWid", "Dialog", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("FileRestoreWid", "\350\256\276\347\275\256\344\270\213\350\275\275\347\232\204\346\226\207\344\273\266\345\220\215", nullptr));
        dlBtn->setText(QCoreApplication::translate("FileRestoreWid", "\344\270\213\350\275\275", nullptr));
        label->setText(QCoreApplication::translate("FileRestoreWid", "\344\270\212\344\274\240\346\227\266\351\227\264", nullptr));
        fastDlBtn->setText(QCoreApplication::translate("FileRestoreWid", "\345\277\253\351\200\237\344\270\213\350\275\275", nullptr));
        label_2->setText(QCoreApplication::translate("FileRestoreWid", "\344\277\235\345\255\230\350\267\257\345\276\204", nullptr));
        dlBtn_2->setText(QCoreApplication::translate("FileRestoreWid", "openBtn", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileRestoreWid: public Ui_FileRestoreWid {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILERESTOREWID_H
