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
    QLineEdit *filenameEdit;
    QPushButton *saveasBtn;
    QLabel *label;
    QPushButton *restoreBtn;
    QLineEdit *backupPathRdit;
    QLabel *label_3;
    QPushButton *pathBtn;
    QLabel *label_2;
    QLineEdit *initpathEdit;

    void setupUi(QDialog *FileRestoreWid)
    {
        if (FileRestoreWid->objectName().isEmpty())
            FileRestoreWid->setObjectName("FileRestoreWid");
        FileRestoreWid->resize(400, 300);
        dateTimeEdit = new QDateTimeEdit(FileRestoreWid);
        dateTimeEdit->setObjectName("dateTimeEdit");
        dateTimeEdit->setGeometry(QRect(100, 90, 271, 41));
        dateTimeEdit->setReadOnly(true);
        filenameEdit = new QLineEdit(FileRestoreWid);
        filenameEdit->setObjectName("filenameEdit");
        filenameEdit->setGeometry(QRect(20, 20, 341, 41));
        saveasBtn = new QPushButton(FileRestoreWid);
        saveasBtn->setObjectName("saveasBtn");
        saveasBtn->setGeometry(QRect(290, 250, 91, 41));
        label = new QLabel(FileRestoreWid);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 90, 71, 41));
        restoreBtn = new QPushButton(FileRestoreWid);
        restoreBtn->setObjectName("restoreBtn");
        restoreBtn->setGeometry(QRect(10, 250, 91, 41));
        backupPathRdit = new QLineEdit(FileRestoreWid);
        backupPathRdit->setObjectName("backupPathRdit");
        backupPathRdit->setGeometry(QRect(100, 190, 271, 41));
        label_3 = new QLabel(FileRestoreWid);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 190, 71, 41));
        pathBtn = new QPushButton(FileRestoreWid);
        pathBtn->setObjectName("pathBtn");
        pathBtn->setGeometry(QRect(150, 250, 91, 41));
        label_2 = new QLabel(FileRestoreWid);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 140, 71, 41));
        initpathEdit = new QLineEdit(FileRestoreWid);
        initpathEdit->setObjectName("initpathEdit");
        initpathEdit->setGeometry(QRect(100, 140, 271, 41));

        retranslateUi(FileRestoreWid);

        QMetaObject::connectSlotsByName(FileRestoreWid);
    } // setupUi

    void retranslateUi(QDialog *FileRestoreWid)
    {
        FileRestoreWid->setWindowTitle(QCoreApplication::translate("FileRestoreWid", "Dialog", nullptr));
        filenameEdit->setPlaceholderText(QCoreApplication::translate("FileRestoreWid", "\350\256\276\347\275\256\344\270\213\350\275\275\347\232\204\346\226\207\344\273\266\345\220\215", nullptr));
        saveasBtn->setText(QCoreApplication::translate("FileRestoreWid", "\345\217\246\345\255\230\344\270\272", nullptr));
        label->setText(QCoreApplication::translate("FileRestoreWid", "\344\270\212\344\274\240\346\227\266\351\227\264", nullptr));
        restoreBtn->setText(QCoreApplication::translate("FileRestoreWid", "\350\277\230\345\216\237\346\226\207\344\273\266", nullptr));
        label_3->setText(QCoreApplication::translate("FileRestoreWid", "\345\244\207\344\273\275\350\267\257\345\276\204", nullptr));
        pathBtn->setText(QCoreApplication::translate("FileRestoreWid", "\351\200\211\346\213\251\347\233\256\345\275\225", nullptr));
        label_2->setText(QCoreApplication::translate("FileRestoreWid", "\345\216\237\350\267\257\345\276\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileRestoreWid: public Ui_FileRestoreWid {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILERESTOREWID_H
