/********************************************************************************
** Form generated from reading UI file 'WidgetFunctional.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETFUNCTIONAL_H
#define UI_WIDGETFUNCTIONAL_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetFunctional
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;

    void setupUi(QWidget *WidgetFunctional)
    {
        if (WidgetFunctional->objectName().isEmpty())
            WidgetFunctional->setObjectName("WidgetFunctional");
        WidgetFunctional->resize(217, 524);
        verticalLayoutWidget = new QWidget(WidgetFunctional);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 0, 141, 521));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_1 = new QPushButton(verticalLayoutWidget);
        pushButton_1->setObjectName("pushButton_1");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_1->sizePolicy().hasHeightForWidth());
        pushButton_1->setSizePolicy(sizePolicy);
        pushButton_1->setMinimumSize(QSize(60, 60));
        pushButton_1->setMaximumSize(QSize(60, 60));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/usedimage/list.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_1->setIcon(icon);

        verticalLayout->addWidget(pushButton_1);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName("pushButton_2");
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setMinimumSize(QSize(60, 60));
        pushButton_2->setMaximumSize(QSize(60, 60));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/usedimage/schedule.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_2->setIcon(icon1);

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(verticalLayoutWidget);
        pushButton_3->setObjectName("pushButton_3");
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);
        pushButton_3->setMinimumSize(QSize(60, 60));
        pushButton_3->setMaximumSize(QSize(60, 60));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/usedimage/editdoc.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_3->setIcon(icon2);

        verticalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(verticalLayoutWidget);
        pushButton_4->setObjectName("pushButton_4");
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);
        pushButton_4->setMaximumSize(QSize(60, 60));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/usedimage/picture.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_4->setIcon(icon3);

        verticalLayout->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(verticalLayoutWidget);
        pushButton_5->setObjectName("pushButton_5");
        sizePolicy.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy);
        pushButton_5->setMaximumSize(QSize(60, 60));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/usedimage/QQ.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_5->setIcon(icon4);

        verticalLayout->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(verticalLayoutWidget);
        pushButton_6->setObjectName("pushButton_6");
        sizePolicy.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy);
        pushButton_6->setMaximumSize(QSize(60, 60));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/usedimage/go.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_6->setIcon(icon5);

        verticalLayout->addWidget(pushButton_6);

        pushButton_7 = new QPushButton(verticalLayoutWidget);
        pushButton_7->setObjectName("pushButton_7");
        sizePolicy.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy);
        pushButton_7->setMaximumSize(QSize(60, 60));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/usedimage/user.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_7->setIcon(icon6);

        verticalLayout->addWidget(pushButton_7);


        retranslateUi(WidgetFunctional);

        QMetaObject::connectSlotsByName(WidgetFunctional);
    } // setupUi

    void retranslateUi(QWidget *WidgetFunctional)
    {
        WidgetFunctional->setWindowTitle(QCoreApplication::translate("WidgetFunctional", "Form", nullptr));
        pushButton_1->setText(QCoreApplication::translate("WidgetFunctional", "\346\226\207\344\273\266\n"
"\346\240\207\347\255\276", nullptr));
        pushButton_2->setText(QCoreApplication::translate("WidgetFunctional", "\345\244\207\345\277\230\n"
"\346\227\245\347\250\213", nullptr));
        pushButton_3->setText(QCoreApplication::translate("WidgetFunctional", "\345\234\250\347\272\277\n"
"\346\226\207\346\241\243", nullptr));
        pushButton_4->setText(QCoreApplication::translate("WidgetFunctional", "\346\211\213\345\206\231\n"
"\347\273\230\345\233\276", nullptr));
        pushButton_5->setText(QCoreApplication::translate("WidgetFunctional", "\351\202\256\344\273\266\n"
"\346\234\215\345\212\241", nullptr));
        pushButton_6->setText(QCoreApplication::translate("WidgetFunctional", "\346\233\264\345\244\232\n"
"\345\212\237\350\203\275", nullptr));
        pushButton_7->setText(QCoreApplication::translate("WidgetFunctional", "\347\224\250\346\210\267\n"
"\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetFunctional: public Ui_WidgetFunctional {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETFUNCTIONAL_H
