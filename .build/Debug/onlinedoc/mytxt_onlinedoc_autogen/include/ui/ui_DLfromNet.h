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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DLfromNet
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *editURL;
    QPushButton *btnDefaultPath;
    QLineEdit *editPath;
    QLabel *label2;
    QProgressBar *progressBar;
    QCheckBox *chkBoxOpen;
    QPushButton *btnDownload;

    void setupUi(QWidget *DLfromNet)
    {
        if (DLfromNet->objectName().isEmpty())
            DLfromNet->setObjectName("DLfromNet");
        DLfromNet->resize(344, 271);
        gridLayout = new QGridLayout(DLfromNet);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(DLfromNet);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        editURL = new QLineEdit(DLfromNet);
        editURL->setObjectName("editURL");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(editURL->sizePolicy().hasHeightForWidth());
        editURL->setSizePolicy(sizePolicy);
        editURL->setCursorPosition(0);
        editURL->setClearButtonEnabled(true);

        gridLayout->addWidget(editURL, 0, 1, 1, 1);

        btnDefaultPath = new QPushButton(DLfromNet);
        btnDefaultPath->setObjectName("btnDefaultPath");

        gridLayout->addWidget(btnDefaultPath, 1, 0, 1, 1);

        editPath = new QLineEdit(DLfromNet);
        editPath->setObjectName("editPath");
        sizePolicy.setHeightForWidth(editPath->sizePolicy().hasHeightForWidth());
        editPath->setSizePolicy(sizePolicy);

        gridLayout->addWidget(editPath, 1, 1, 1, 1);

        label2 = new QLabel(DLfromNet);
        label2->setObjectName("label2");

        gridLayout->addWidget(label2, 2, 0, 1, 1);

        progressBar = new QProgressBar(DLfromNet);
        progressBar->setObjectName("progressBar");
        sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy);
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 2, 1, 1, 1);

        chkBoxOpen = new QCheckBox(DLfromNet);
        chkBoxOpen->setObjectName("chkBoxOpen");
        chkBoxOpen->setChecked(true);

        gridLayout->addWidget(chkBoxOpen, 3, 0, 1, 1);

        btnDownload = new QPushButton(DLfromNet);
        btnDownload->setObjectName("btnDownload");
        btnDownload->setMaximumSize(QSize(10000, 16777215));

        gridLayout->addWidget(btnDownload, 3, 1, 1, 1);

        QWidget::setTabOrder(editURL, btnDefaultPath);
        QWidget::setTabOrder(btnDefaultPath, editPath);
        QWidget::setTabOrder(editPath, chkBoxOpen);
        QWidget::setTabOrder(chkBoxOpen, btnDownload);

        retranslateUi(DLfromNet);

        QMetaObject::connectSlotsByName(DLfromNet);
    } // setupUi

    void retranslateUi(QWidget *DLfromNet)
    {
        DLfromNet->setWindowTitle(QCoreApplication::translate("DLfromNet", "Form", nullptr));
        label->setText(QCoreApplication::translate("DLfromNet", "URL:", nullptr));
        editURL->setText(QString());
        btnDefaultPath->setText(QCoreApplication::translate("DLfromNet", "\351\200\211\346\213\251\n"
"\350\267\257\345\276\204", nullptr));
        label2->setText(QCoreApplication::translate("DLfromNet", "\344\270\213\350\275\275\350\277\233\345\272\246", nullptr));
        chkBoxOpen->setText(QCoreApplication::translate("DLfromNet", "\345\256\214\346\210\220\345\220\216\346\211\223\345\274\200", nullptr));
        btnDownload->setText(QCoreApplication::translate("DLfromNet", "\344\270\213\350\275\275", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DLfromNet: public Ui_DLfromNet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLFROMNET_H
