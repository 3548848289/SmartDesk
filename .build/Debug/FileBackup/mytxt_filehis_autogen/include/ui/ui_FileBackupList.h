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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileBackupList
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QLabel *label_2;
    QListWidget *backupList;
    QComboBox *fileListComboBox;
    QLabel *label;

    void setupUi(QWidget *FileBackupList)
    {
        if (FileBackupList->objectName().isEmpty())
            FileBackupList->setObjectName("FileBackupList");
        FileBackupList->resize(400, 381);
        gridLayout = new QGridLayout(FileBackupList);
        gridLayout->setObjectName("gridLayout");
        pushButton = new QPushButton(FileBackupList);
        pushButton->setObjectName("pushButton");

        gridLayout->addWidget(pushButton, 4, 0, 1, 1);

        label_2 = new QLabel(FileBackupList);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        backupList = new QListWidget(FileBackupList);
        backupList->setObjectName("backupList");
        backupList->setSpacing(8);

        gridLayout->addWidget(backupList, 3, 0, 1, 1);

        fileListComboBox = new QComboBox(FileBackupList);
        fileListComboBox->setObjectName("fileListComboBox");

        gridLayout->addWidget(fileListComboBox, 1, 0, 1, 1);

        label = new QLabel(FileBackupList);
        label->setObjectName("label");

        gridLayout->addWidget(label, 2, 0, 1, 1);


        retranslateUi(FileBackupList);

        QMetaObject::connectSlotsByName(FileBackupList);
    } // setupUi

    void retranslateUi(QWidget *FileBackupList)
    {
        FileBackupList->setWindowTitle(QCoreApplication::translate("FileBackupList", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("FileBackupList", "\346\233\277\346\215\242\n"
"\346\226\207\344\273\266", nullptr));
        label_2->setText(QCoreApplication::translate("FileBackupList", "\346\217\220\344\272\244\350\277\207\347\232\204\346\226\207\344\273\266", nullptr));
        label->setText(QCoreApplication::translate("FileBackupList", "\346\217\220\344\272\244\345\216\206\345\217\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileBackupList: public Ui_FileBackupList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEBACKUPLIST_H
