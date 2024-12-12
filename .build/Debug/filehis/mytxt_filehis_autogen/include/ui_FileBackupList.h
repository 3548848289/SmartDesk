/********************************************************************************
** Form generated from reading UI file 'FileBackupList.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEBACKUPLIST_H
#define UI_FILEBACKUPLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileBackupList
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QListWidget *listWidget;

    void setupUi(QWidget *FileBackupList)
    {
        if (FileBackupList->objectName().isEmpty())
            FileBackupList->setObjectName("FileBackupList");
        FileBackupList->resize(400, 199);
        gridLayout = new QGridLayout(FileBackupList);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(FileBackupList);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        listWidget = new QListWidget(FileBackupList);
        listWidget->setObjectName("listWidget");

        gridLayout->addWidget(listWidget, 1, 0, 1, 1);


        retranslateUi(FileBackupList);

        QMetaObject::connectSlotsByName(FileBackupList);
    } // setupUi

    void retranslateUi(QWidget *FileBackupList)
    {
        FileBackupList->setWindowTitle(QCoreApplication::translate("FileBackupList", "Form", nullptr));
        label->setText(QCoreApplication::translate("FileBackupList", "\346\226\207\344\273\266\346\217\220\344\272\244\345\216\206\345\217\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileBackupList: public Ui_FileBackupList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEBACKUPLIST_H
