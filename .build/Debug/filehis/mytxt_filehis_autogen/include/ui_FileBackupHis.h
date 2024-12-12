/********************************************************************************
** Form generated from reading UI file 'FileBackupHis.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEBACKUPHIS_H
#define UI_FILEBACKUPHIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileBackupHis
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QListWidget *listWidget;

    void setupUi(QWidget *FileBackupHis)
    {
        if (FileBackupHis->objectName().isEmpty())
            FileBackupHis->setObjectName("FileBackupHis");
        FileBackupHis->resize(400, 199);
        gridLayout = new QGridLayout(FileBackupHis);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(FileBackupHis);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        listWidget = new QListWidget(FileBackupHis);
        listWidget->setObjectName("listWidget");

        gridLayout->addWidget(listWidget, 1, 0, 1, 1);


        retranslateUi(FileBackupHis);

        QMetaObject::connectSlotsByName(FileBackupHis);
    } // setupUi

    void retranslateUi(QWidget *FileBackupHis)
    {
        FileBackupHis->setWindowTitle(QCoreApplication::translate("FileBackupHis", "Form", nullptr));
        label->setText(QCoreApplication::translate("FileBackupHis", "\346\226\207\344\273\266\346\217\220\344\272\244\345\216\206\345\217\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileBackupHis: public Ui_FileBackupHis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEBACKUPHIS_H
