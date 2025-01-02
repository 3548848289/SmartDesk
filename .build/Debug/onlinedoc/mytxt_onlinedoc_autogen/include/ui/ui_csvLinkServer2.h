/********************************************************************************
** Form generated from reading UI file 'csvLinkServer2.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CSVLINKSERVER2_H
#define UI_CSVLINKSERVER2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_csvLinkServer2
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *passwdEdit;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QTextEdit *textBrowser;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *sendmsgEdit;
    QLineEdit *msgEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *buildBtn;
    QLineEdit *readfileEdit_2;

    void setupUi(QWidget *csvLinkServer2)
    {
        if (csvLinkServer2->objectName().isEmpty())
            csvLinkServer2->setObjectName("csvLinkServer2");
        csvLinkServer2->resize(335, 514);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(csvLinkServer2->sizePolicy().hasHeightForWidth());
        csvLinkServer2->setSizePolicy(sizePolicy);
        csvLinkServer2->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(csvLinkServer2);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(7);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(-1, -1, 0, -1);
        label_2 = new QLabel(csvLinkServer2);
        label_2->setObjectName("label_2");

        horizontalLayout_4->addWidget(label_2);

        passwdEdit = new QLineEdit(csvLinkServer2);
        passwdEdit->setObjectName("passwdEdit");

        horizontalLayout_4->addWidget(passwdEdit);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 4);

        gridLayout->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        tableWidget = new QTableWidget(csvLinkServer2);
        tableWidget->setObjectName("tableWidget");

        gridLayout->addWidget(tableWidget, 1, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label = new QLabel(csvLinkServer2);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_5->addWidget(label);

        textBrowser = new QTextEdit(csvLinkServer2);
        textBrowser->setObjectName("textBrowser");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(textBrowser);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 10);

        gridLayout->addLayout(horizontalLayout_5, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        sendmsgEdit = new QPushButton(csvLinkServer2);
        sendmsgEdit->setObjectName("sendmsgEdit");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(sendmsgEdit->sizePolicy().hasHeightForWidth());
        sendmsgEdit->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(sendmsgEdit);

        msgEdit = new QLineEdit(csvLinkServer2);
        msgEdit->setObjectName("msgEdit");

        horizontalLayout_3->addWidget(msgEdit);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 10);

        gridLayout->addLayout(horizontalLayout_3, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        buildBtn = new QPushButton(csvLinkServer2);
        buildBtn->setObjectName("buildBtn");

        horizontalLayout->addWidget(buildBtn);

        readfileEdit_2 = new QLineEdit(csvLinkServer2);
        readfileEdit_2->setObjectName("readfileEdit_2");

        horizontalLayout->addWidget(readfileEdit_2);


        gridLayout->addLayout(horizontalLayout, 4, 0, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 2);
        gridLayout->setRowStretch(2, 2);
        gridLayout->setRowStretch(3, 1);
        gridLayout->setRowStretch(4, 1);

        retranslateUi(csvLinkServer2);

        QMetaObject::connectSlotsByName(csvLinkServer2);
    } // setupUi

    void retranslateUi(QWidget *csvLinkServer2)
    {
        csvLinkServer2->setWindowTitle(QCoreApplication::translate("csvLinkServer2", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("csvLinkServer2", "\350\276\223\345\205\245\345\217\243\344\273\244", nullptr));
        passwdEdit->setText(QCoreApplication::translate("csvLinkServer2", "K7i6LfSp", nullptr));
        label->setText(QCoreApplication::translate("csvLinkServer2", "\345\205\254\n"
"\345\221\212\n"
"\346\240\217", nullptr));
        sendmsgEdit->setText(QCoreApplication::translate("csvLinkServer2", "\345\217\221\n"
"\344\277\241\346\201\257", nullptr));
        buildBtn->setText(QCoreApplication::translate("csvLinkServer2", "\345\277\253\351\200\237\345\273\272\347\253\213\n"
"\345\205\261\344\272\253\346\226\207\344\273\266", nullptr));
        readfileEdit_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class csvLinkServer2: public Ui_csvLinkServer2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CSVLINKSERVER2_H
