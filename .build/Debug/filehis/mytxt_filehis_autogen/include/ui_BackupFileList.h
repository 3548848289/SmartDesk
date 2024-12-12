/********************************************************************************
** Form generated from reading UI file 'BackupFileList.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BACKUPFILELIST_H
#define UI_BACKUPFILELIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BackupFileList
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QListWidget *listWidget;

    void setupUi(QWidget *BackupFileList)
    {
        if (BackupFileList->objectName().isEmpty())
            BackupFileList->setObjectName("BackupFileList");
        BackupFileList->resize(400, 199);
        gridLayout = new QGridLayout(BackupFileList);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(BackupFileList);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        listWidget = new QListWidget(BackupFileList);
        listWidget->setObjectName("listWidget");

        gridLayout->addWidget(listWidget, 1, 0, 1, 1);


        retranslateUi(BackupFileList);

        QMetaObject::connectSlotsByName(BackupFileList);
    } // setupUi

    void retranslateUi(QWidget *BackupFileList)
    {
        BackupFileList->setWindowTitle(QCoreApplication::translate("BackupFileList", "Form", nullptr));
        label->setText(QCoreApplication::translate("BackupFileList", "\346\226\207\344\273\266\346\217\220\344\272\244\345\216\206\345\217\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BackupFileList: public Ui_BackupFileList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACKUPFILELIST_H
