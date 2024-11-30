/********************************************************************************
** Form generated from reading UI file 'sendemail.ui'
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
#include <QtWidgets/QFormLayout>
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
    QLabel *label_7;
    QFormLayout *formLayout;
    QLabel *label_8;
    QLineEdit *sender;
    QLabel *label_9;
    QLineEdit *recipients;
    QLabel *label_10;
    QLineEdit *subject;
    QTextEdit *texteditor;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QPushButton *addAttachment;
    QListWidget *attachments;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *sendEmail;
    QPushButton *pushButton;
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

        label_7 = new QLabel(SendEmail);
        label_7->setObjectName("label_7");
        QFont font;
        font.setBold(true);
        label_7->setFont(font);

        verticalLayout->addWidget(label_7);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setFieldGrowthPolicy(QFormLayout::FieldGrowthPolicy::AllNonFixedFieldsGrow);
        formLayout->setRowWrapPolicy(QFormLayout::RowWrapPolicy::DontWrapRows);
        formLayout->setHorizontalSpacing(0);
        formLayout->setVerticalSpacing(8);
        formLayout->setContentsMargins(0, 10, -1, 0);
        label_8 = new QLabel(SendEmail);
        label_8->setObjectName("label_8");
        label_8->setMinimumSize(QSize(81, 0));
        label_8->setMaximumSize(QSize(81, 16777215));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_8);

        sender = new QLineEdit(SendEmail);
        sender->setObjectName("sender");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sender->sizePolicy().hasHeightForWidth());
        sender->setSizePolicy(sizePolicy);

        formLayout->setWidget(0, QFormLayout::FieldRole, sender);

        label_9 = new QLabel(SendEmail);
        label_9->setObjectName("label_9");
        label_9->setMinimumSize(QSize(81, 0));
        label_9->setMaximumSize(QSize(81, 16777215));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_9);

        recipients = new QLineEdit(SendEmail);
        recipients->setObjectName("recipients");
        sizePolicy.setHeightForWidth(recipients->sizePolicy().hasHeightForWidth());
        recipients->setSizePolicy(sizePolicy);

        formLayout->setWidget(1, QFormLayout::FieldRole, recipients);

        label_10 = new QLabel(SendEmail);
        label_10->setObjectName("label_10");
        label_10->setMinimumSize(QSize(81, 0));
        label_10->setMaximumSize(QSize(81, 16777215));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_10);

        subject = new QLineEdit(SendEmail);
        subject->setObjectName("subject");
        sizePolicy.setHeightForWidth(subject->sizePolicy().hasHeightForWidth());
        subject->setSizePolicy(sizePolicy);

        formLayout->setWidget(2, QFormLayout::FieldRole, subject);


        verticalLayout->addLayout(formLayout);

        texteditor = new QTextEdit(SendEmail);
        texteditor->setObjectName("texteditor");
        texteditor->setTextInteractionFlags(Qt::TextInteractionFlag::LinksAccessibleByKeyboard|Qt::TextInteractionFlag::LinksAccessibleByMouse|Qt::TextInteractionFlag::TextBrowserInteraction|Qt::TextInteractionFlag::TextEditable|Qt::TextInteractionFlag::TextEditorInteraction|Qt::TextInteractionFlag::TextSelectableByKeyboard|Qt::TextInteractionFlag::TextSelectableByMouse);

        verticalLayout->addWidget(texteditor);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_3 = new QLabel(SendEmail);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);

        addAttachment = new QPushButton(SendEmail);
        addAttachment->setObjectName("addAttachment");
        addAttachment->setMinimumSize(QSize(97, 0));
        addAttachment->setMaximumSize(QSize(97, 16777215));

        horizontalLayout->addWidget(addAttachment);


        verticalLayout->addLayout(horizontalLayout);

        attachments = new QListWidget(SendEmail);
        attachments->setObjectName("attachments");
        attachments->setMaximumSize(QSize(16777215, 64));

        verticalLayout->addWidget(attachments);

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

        pushButton = new QPushButton(SendEmail);
        pushButton->setObjectName("pushButton");

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 1);
        horizontalLayout_2->setStretch(3, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout->setStretch(2, 5);
        verticalLayout->setStretch(3, 10);
        verticalLayout->setStretch(4, 1);
        verticalLayout->setStretch(5, 2);
        verticalLayout->setStretch(6, 2);

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

        label_7->setText(QCoreApplication::translate("SendEmail", "Mime \351\202\256\344\273\266", nullptr));
        label_8->setText(QCoreApplication::translate("SendEmail", "\345\217\221\344\273\266\344\272\272\357\274\232", nullptr));
        label_9->setText(QCoreApplication::translate("SendEmail", "\346\224\266\344\273\266\344\272\272\357\274\232", nullptr));
        label_10->setText(QCoreApplication::translate("SendEmail", "\344\270\273\351\242\230\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("SendEmail", "\351\231\204\344\273\266\357\274\232", nullptr));
        addAttachment->setText(QCoreApplication::translate("SendEmail", "\346\267\273\345\212\240\346\226\207\344\273\266", nullptr));
        sendEmail->setText(QCoreApplication::translate("SendEmail", "\345\217\221\351\200\201\351\202\256\344\273\266", nullptr));
        pushButton->setText(QCoreApplication::translate("SendEmail", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SendEmail: public Ui_SendEmail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDEMAIL_H
