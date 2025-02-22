/********************************************************************************
** Form generated from reading UI file 'DLogin.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLOGIN_H
#define UI_DLOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DLogin
{
public:
    QWidget *center_widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_1;
    QLabel *statusLabel;
    QToolButton *exit_toolButton;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *avatar_pushButton;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *horizontalLayout_3;
    QWidget *loginwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *username;
    QLineEdit *password;
    QRadioButton *radioButton;
    QHBoxLayout *horizontalLayout;
    QPushButton *registerBtn;
    QPushButton *loginBtn;
    QPushButton *login_pushButton_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *resiger_pushButton;
    QFrame *line;
    QPushButton *forget_pushButton;

    void setupUi(QDialog *DLogin)
    {
        if (DLogin->objectName().isEmpty())
            DLogin->setObjectName("DLogin");
        DLogin->resize(270, 436);
        DLogin->setStyleSheet(QString::fromUtf8("QDialog {\n"
"    border: 1px solid #D6D4D4; \n"
"	border-radius: 15px;\n"
"}\n"
"\n"
"QToolButton{\n"
"	background-color: rgba(0, 0, 0,0);\n"
"	border: none;\n"
"}\n"
"\n"
"\n"
"QLabel#profile_label{\n"
"	background-color: rgb(255, 255, 255);\n"
"	border-radius: 45px;\n"
"}\n"
"\n"
"QLineEdit{\n"
"	border: none;\n"
"	border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton{\n"
"	background-color: rgba(0, 0, 0, 0);\n"
"}\n"
"\n"
"QPushButton#loginBtn{\n"
"	background-color: rgb(158, 218, 255);\n"
"	color: rgb(255, 255, 255);\n"
"	border: none;\n"
"	border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton#registerBtn{\n"
"	background-color: rgb(158, 218, 255);\n"
"	color: rgb(255, 255, 255);\n"
"	border: none;\n"
"	border-radius: 10px;\n"
"}"));
        center_widget = new QWidget(DLogin);
        center_widget->setObjectName("center_widget");
        center_widget->setGeometry(QRect(10, 20, 241, 381));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(center_widget->sizePolicy().hasHeightForWidth());
        center_widget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(center_widget);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setObjectName("horizontalLayout_1");
        statusLabel = new QLabel(center_widget);
        statusLabel->setObjectName("statusLabel");

        horizontalLayout_1->addWidget(statusLabel);

        exit_toolButton = new QToolButton(center_widget);
        exit_toolButton->setObjectName("exit_toolButton");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/usedimage/close-white.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        exit_toolButton->setIcon(icon);
        exit_toolButton->setIconSize(QSize(24, 24));

        horizontalLayout_1->addWidget(exit_toolButton);


        verticalLayout->addLayout(horizontalLayout_1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        avatar_pushButton = new QPushButton(center_widget);
        avatar_pushButton->setObjectName("avatar_pushButton");
        avatar_pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    color: #003366;\n"
"    background-color: #B5FFFA;  \n"
"    border: 1px solid #003366; \n"
"    border-radius: 25px; \n"
"    padding: 10px;  \n"
"    width: 50px; \n"
"    height: 50px;\n"
"    text-align: center; \n"
"}\n"
""));

        horizontalLayout_2->addWidget(avatar_pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QVBoxLayout();
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        loginwidget = new QWidget(center_widget);
        loginwidget->setObjectName("loginwidget");
        verticalLayoutWidget = new QWidget(loginwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 10, 219, 298));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setSpacing(20);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        username = new QLineEdit(verticalLayoutWidget);
        username->setObjectName("username");
        username->setMinimumSize(QSize(0, 40));
        QFont font;
        font.setPointSize(11);
        username->setFont(font);

        verticalLayout_2->addWidget(username);

        password = new QLineEdit(verticalLayoutWidget);
        password->setObjectName("password");
        password->setMinimumSize(QSize(0, 40));
        password->setFont(font);

        verticalLayout_2->addWidget(password);

        radioButton = new QRadioButton(verticalLayoutWidget);
        radioButton->setObjectName("radioButton");

        verticalLayout_2->addWidget(radioButton);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        registerBtn = new QPushButton(verticalLayoutWidget);
        registerBtn->setObjectName("registerBtn");
        registerBtn->setEnabled(false);
        registerBtn->setMinimumSize(QSize(0, 35));

        horizontalLayout->addWidget(registerBtn);

        loginBtn = new QPushButton(verticalLayoutWidget);
        loginBtn->setObjectName("loginBtn");
        loginBtn->setEnabled(false);
        loginBtn->setMinimumSize(QSize(0, 35));

        horizontalLayout->addWidget(loginBtn);


        verticalLayout_2->addLayout(horizontalLayout);

        login_pushButton_2 = new QPushButton(verticalLayoutWidget);
        login_pushButton_2->setObjectName("login_pushButton_2");
        login_pushButton_2->setEnabled(false);
        login_pushButton_2->setMinimumSize(QSize(0, 35));

        verticalLayout_2->addWidget(login_pushButton_2);


        horizontalLayout_3->addWidget(loginwidget);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(51);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        resiger_pushButton = new QPushButton(center_widget);
        resiger_pushButton->setObjectName("resiger_pushButton");

        horizontalLayout_4->addWidget(resiger_pushButton);

        line = new QFrame(center_widget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_4->addWidget(line);

        forget_pushButton = new QPushButton(center_widget);
        forget_pushButton->setObjectName("forget_pushButton");

        horizontalLayout_4->addWidget(forget_pushButton);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 2);
        verticalLayout->setStretch(2, 6);
        QWidget::setTabOrder(avatar_pushButton, username);
        QWidget::setTabOrder(username, password);
        QWidget::setTabOrder(password, radioButton);
        QWidget::setTabOrder(radioButton, registerBtn);
        QWidget::setTabOrder(registerBtn, loginBtn);
        QWidget::setTabOrder(loginBtn, resiger_pushButton);
        QWidget::setTabOrder(resiger_pushButton, forget_pushButton);
        QWidget::setTabOrder(forget_pushButton, login_pushButton_2);
        QWidget::setTabOrder(login_pushButton_2, exit_toolButton);

        retranslateUi(DLogin);

        QMetaObject::connectSlotsByName(DLogin);
    } // setupUi

    void retranslateUi(QDialog *DLogin)
    {
        DLogin->setWindowTitle(QCoreApplication::translate("DLogin", "Dialog", nullptr));
        statusLabel->setText(QCoreApplication::translate("DLogin", "\346\254\242\350\277\216", nullptr));
        exit_toolButton->setText(QCoreApplication::translate("DLogin", "\351\200\200\345\207\272\347\231\273\345\275\225", nullptr));
        avatar_pushButton->setText(QString());
        username->setPlaceholderText(QCoreApplication::translate("DLogin", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215", nullptr));
        password->setPlaceholderText(QCoreApplication::translate("DLogin", "\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        radioButton->setText(QCoreApplication::translate("DLogin", "\345\267\262\351\230\205\350\257\273\345\271\266\345\220\214\346\204\217\346\234\215\345\212\241\345\215\217\350\256\256", nullptr));
        registerBtn->setText(QCoreApplication::translate("DLogin", "\346\263\250\345\206\214", nullptr));
        loginBtn->setText(QCoreApplication::translate("DLogin", "\347\231\273\345\275\225", nullptr));
        login_pushButton_2->setText(QCoreApplication::translate("DLogin", "\346\263\250\345\206\214", nullptr));
        resiger_pushButton->setText(QCoreApplication::translate("DLogin", "\346\233\264\345\244\232\344\277\241\346\201\257", nullptr));
        forget_pushButton->setText(QCoreApplication::translate("DLogin", "\345\277\230\350\256\260\345\257\206\347\240\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DLogin: public Ui_DLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLOGIN_H
