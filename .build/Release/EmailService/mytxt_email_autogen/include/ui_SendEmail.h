/********************************************************************************
** Form generated from reading UI file 'SendEmail.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENDEMAIL_H
#define UI_SENDEMAIL_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SendEmail
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QSpinBox *port;
    QLabel *label_2;
    QLineEdit *host;
    QLabel *label;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *username;
    QLineEdit *password;
    QComboBox *security;
    QLineEdit *sender;
    QLineEdit *recipients;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *subject;
    QTextEdit *texteditor;
    QVBoxLayout *verticalLayout_2;
    QPushButton *addAttachment;
    QListWidget *attachments;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *sendEmail;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *SendEmail)
    {
        if (SendEmail->objectName().isEmpty())
            SendEmail->setObjectName("SendEmail");
        SendEmail->resize(370, 353);
        gridLayout_2 = new QGridLayout(SendEmail);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        port = new QSpinBox(SendEmail);
        port->setObjectName("port");
        port->setMinimum(1);
        port->setMaximum(99999);
        port->setValue(25);

        gridLayout->addWidget(port, 0, 3, 1, 1);

        label_2 = new QLabel(SendEmail);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(34, 17));
        label_2->setMaximumSize(QSize(34, 17));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        host = new QLineEdit(SendEmail);
        host->setObjectName("host");

        gridLayout->addWidget(host, 0, 1, 1, 1);

        label = new QLabel(SendEmail);
        label->setObjectName("label");
        label->setMinimumSize(QSize(87, 17));
        label->setMaximumSize(QSize(87, 17));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_5 = new QLabel(SendEmail);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        label_6 = new QLabel(SendEmail);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 1, 2, 1, 1);

        username = new QLineEdit(SendEmail);
        username->setObjectName("username");

        gridLayout->addWidget(username, 1, 1, 1, 1);

        password = new QLineEdit(SendEmail);
        password->setObjectName("password");
        password->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayout->addWidget(password, 1, 3, 1, 3);

        security = new QComboBox(SendEmail);
        security->addItem(QString());
        security->addItem(QString());
        security->addItem(QString());
        security->setObjectName("security");

        gridLayout->addWidget(security, 0, 4, 1, 1);


        verticalLayout->addLayout(gridLayout);

        sender = new QLineEdit(SendEmail);
        sender->setObjectName("sender");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sender->sizePolicy().hasHeightForWidth());
        sender->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(sender);

        recipients = new QLineEdit(SendEmail);
        recipients->setObjectName("recipients");
        sizePolicy.setHeightForWidth(recipients->sizePolicy().hasHeightForWidth());
        recipients->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(recipients);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        subject = new QLineEdit(SendEmail);
        subject->setObjectName("subject");
        sizePolicy.setHeightForWidth(subject->sizePolicy().hasHeightForWidth());
        subject->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(subject);

        texteditor = new QTextEdit(SendEmail);
        texteditor->setObjectName("texteditor");
        texteditor->setTextInteractionFlags(Qt::TextInteractionFlag::LinksAccessibleByKeyboard|Qt::TextInteractionFlag::LinksAccessibleByMouse|Qt::TextInteractionFlag::TextBrowserInteraction|Qt::TextInteractionFlag::TextEditable|Qt::TextInteractionFlag::TextEditorInteraction|Qt::TextInteractionFlag::TextSelectableByKeyboard|Qt::TextInteractionFlag::TextSelectableByMouse);

        verticalLayout_3->addWidget(texteditor);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 9);

        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName("verticalLayout_2");
        addAttachment = new QPushButton(SendEmail);
        addAttachment->setObjectName("addAttachment");
        sizePolicy.setHeightForWidth(addAttachment->sizePolicy().hasHeightForWidth());
        addAttachment->setSizePolicy(sizePolicy);
        addAttachment->setMaximumSize(QSize(97, 16777215));

        verticalLayout_2->addWidget(addAttachment);

        attachments = new QListWidget(SendEmail);
        attachments->setObjectName("attachments");

        verticalLayout_2->addWidget(attachments);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 9);

        horizontalLayout_3->addLayout(verticalLayout_2);

        horizontalLayout_3->setStretch(0, 3);
        horizontalLayout_3->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        sendEmail = new QPushButton(SendEmail);
        sendEmail->setObjectName("sendEmail");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(sendEmail->sizePolicy().hasHeightForWidth());
        sendEmail->setSizePolicy(sizePolicy1);
        sendEmail->setMinimumSize(QSize(29, 0));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSend));
        sendEmail->setIcon(icon);

        horizontalLayout_2->addWidget(sendEmail);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 1);
        horizontalLayout_2->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 5);
        verticalLayout->setStretch(4, 1);

        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(SendEmail);

        QMetaObject::connectSlotsByName(SendEmail);
    } // setupUi

    void retranslateUi(QWidget *SendEmail)
    {
        SendEmail->setWindowTitle(QCoreApplication::translate("SendEmail", "\345\217\221\351\200\201\347\224\265\345\255\220\351\202\256\344\273\266", nullptr));
        label_2->setText(QCoreApplication::translate("SendEmail", "\347\253\257\345\217\243\357\274\232", nullptr));
        host->setText(QCoreApplication::translate("SendEmail", "localhost", nullptr));
        label->setText(QCoreApplication::translate("SendEmail", "SMTP \346\234\215\345\212\241\345\231\250\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("SendEmail", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_6->setText(QCoreApplication::translate("SendEmail", "\345\257\206\347\240\201\357\274\232", nullptr));
        security->setItemText(0, QCoreApplication::translate("SendEmail", "\346\234\252\345\212\240\345\257\206", nullptr));
        security->setItemText(1, QCoreApplication::translate("SendEmail", "SSL", nullptr));
        security->setItemText(2, QCoreApplication::translate("SendEmail", "TLS/STARTTLS", nullptr));

        sender->setInputMask(QString());
        sender->setText(QString());
        sender->setPlaceholderText(QCoreApplication::translate("SendEmail", "\345\217\221\344\273\266\344\272\272", nullptr));
        recipients->setInputMask(QString());
        recipients->setText(QString());
        recipients->setPlaceholderText(QCoreApplication::translate("SendEmail", "\346\224\266\344\273\266\344\272\272", nullptr));
        addAttachment->setText(QCoreApplication::translate("SendEmail", "\346\267\273\345\212\240\346\226\207\344\273\266", nullptr));
        sendEmail->setText(QCoreApplication::translate("SendEmail", "\345\217\221\351\200\201\351\202\256\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SendEmail: public Ui_SendEmail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDEMAIL_H
