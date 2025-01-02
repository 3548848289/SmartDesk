/********************************************************************************
** Form generated from reading UI file 'FileBackupView.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEBACKUPVIEW_H
#define UI_FILEBACKUPVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileBackupView
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *fileListComboBox;
    QPushButton *pushButton;
    QLabel *label;
    QListWidget *backupList;

    void setupUi(QWidget *FileBackupView)
    {
        if (FileBackupView->objectName().isEmpty())
            FileBackupView->setObjectName("FileBackupView");
        FileBackupView->resize(400, 381);
        gridLayout = new QGridLayout(FileBackupView);
        gridLayout->setObjectName("gridLayout");
        label_2 = new QLabel(FileBackupView);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        fileListComboBox = new QComboBox(FileBackupView);
        fileListComboBox->setObjectName("fileListComboBox");

        horizontalLayout_3->addWidget(fileListComboBox);

        pushButton = new QPushButton(FileBackupView);
        pushButton->setObjectName("pushButton");
        pushButton->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(pushButton);

        horizontalLayout_3->setStretch(0, 7);

        gridLayout->addLayout(horizontalLayout_3, 3, 0, 1, 1);

        label = new QLabel(FileBackupView);
        label->setObjectName("label");

        gridLayout->addWidget(label, 5, 0, 1, 1);

        backupList = new QListWidget(FileBackupView);
        backupList->setObjectName("backupList");
        backupList->setSpacing(8);

        gridLayout->addWidget(backupList, 6, 0, 1, 1);


        retranslateUi(FileBackupView);

        QMetaObject::connectSlotsByName(FileBackupView);
    } // setupUi

    void retranslateUi(QWidget *FileBackupView)
    {
        FileBackupView->setWindowTitle(QCoreApplication::translate("FileBackupView", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("FileBackupView", "\346\217\220\344\272\244\350\277\207\347\232\204\346\226\207\344\273\266", nullptr));
        pushButton->setText(QCoreApplication::translate("FileBackupView", "\350\260\203\346\225\264", nullptr));
        label->setText(QCoreApplication::translate("FileBackupView", "\346\217\220\344\272\244\345\216\206\345\217\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileBackupView: public Ui_FileBackupView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEBACKUPVIEW_H
