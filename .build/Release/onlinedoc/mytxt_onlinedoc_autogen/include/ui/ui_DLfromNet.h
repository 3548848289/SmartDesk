/********************************************************************************
** Form generated from reading UI file 'DLfromNet.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLFROMNET_H
#define UI_DLFROMNET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DLfromNet
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QProgressBar *progressBar;
    QLabel *label;
    QLineEdit *editPath;
    QLineEdit *editURL;
    QLabel *label_3;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnDownload;
    QPushButton *btnDefaultPath;
    QCheckBox *chkBoxOpen;

    void setupUi(QWidget *DLfromNet)
    {
        if (DLfromNet->objectName().isEmpty())
            DLfromNet->setObjectName("DLfromNet");
        DLfromNet->resize(344, 276);
        gridLayout_2 = new QGridLayout(DLfromNet);
        gridLayout_2->setObjectName("gridLayout_2");
        groupBox_2 = new QGroupBox(DLfromNet);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(5);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 15, 0);
        progressBar = new QProgressBar(groupBox_2);
        progressBar->setObjectName("progressBar");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy);
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 3, 1, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        editPath = new QLineEdit(groupBox_2);
        editPath->setObjectName("editPath");
        sizePolicy.setHeightForWidth(editPath->sizePolicy().hasHeightForWidth());
        editPath->setSizePolicy(sizePolicy);

        gridLayout->addWidget(editPath, 2, 1, 1, 1);

        editURL = new QLineEdit(groupBox_2);
        editURL->setObjectName("editURL");
        sizePolicy.setHeightForWidth(editURL->sizePolicy().hasHeightForWidth());
        editURL->setSizePolicy(sizePolicy);
        editURL->setCursorPosition(0);
        editURL->setClearButtonEnabled(true);

        gridLayout->addWidget(editURL, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, -1, 15, -1);
        btnDownload = new QPushButton(groupBox_2);
        btnDownload->setObjectName("btnDownload");
        btnDownload->setMaximumSize(QSize(10000, 16777215));

        horizontalLayout->addWidget(btnDownload);

        btnDefaultPath = new QPushButton(groupBox_2);
        btnDefaultPath->setObjectName("btnDefaultPath");

        horizontalLayout->addWidget(btnDefaultPath);


        gridLayout->addLayout(horizontalLayout, 4, 1, 1, 1);

        chkBoxOpen = new QCheckBox(groupBox_2);
        chkBoxOpen->setObjectName("chkBoxOpen");
        chkBoxOpen->setChecked(true);

        gridLayout->addWidget(chkBoxOpen, 4, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 0, 0, 1, 1);


        retranslateUi(DLfromNet);

        QMetaObject::connectSlotsByName(DLfromNet);
    } // setupUi

    void retranslateUi(QWidget *DLfromNet)
    {
        DLfromNet->setWindowTitle(QCoreApplication::translate("DLfromNet", "Form", nullptr));
        groupBox_2->setTitle(QString());
        label->setText(QCoreApplication::translate("DLfromNet", "URL:", nullptr));
        editURL->setText(QCoreApplication::translate("DLfromNet", "192.168.41.128/a.txt", nullptr));
        label_3->setText(QCoreApplication::translate("DLfromNet", "\344\270\213\350\275\275\350\277\233\345\272\246", nullptr));
        label_2->setText(QCoreApplication::translate("DLfromNet", "\344\277\235\345\255\230\350\267\257\345\276\204", nullptr));
        btnDownload->setText(QCoreApplication::translate("DLfromNet", "\344\270\213\350\275\275", nullptr));
        btnDefaultPath->setText(QCoreApplication::translate("DLfromNet", "\351\273\230\350\256\244\350\267\257\345\276\204", nullptr));
        chkBoxOpen->setText(QCoreApplication::translate("DLfromNet", "\345\256\214\346\210\220\345\220\216\346\211\223\345\274\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DLfromNet: public Ui_DLfromNet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLFROMNET_H
