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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetFunctional
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton_8;
    QPushButton *pushButton_6;
    QPushButton *pushButton_1;
    QPushButton *pushButton_4;
    QPushButton *pushButton_7;
    QPushButton *pushButton_5;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_9;

    void setupUi(QWidget *WidgetFunctional)
    {
        if (WidgetFunctional->objectName().isEmpty())
            WidgetFunctional->setObjectName("WidgetFunctional");
        WidgetFunctional->resize(72, 556);
        gridLayout = new QGridLayout(WidgetFunctional);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(-1, 0, -1, 0);
        pushButton_8 = new QPushButton(WidgetFunctional);
        pushButton_8->setObjectName("pushButton_8");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_8->sizePolicy().hasHeightForWidth());
        pushButton_8->setSizePolicy(sizePolicy);
        pushButton_8->setMaximumSize(QSize(60, 60));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::SystemSearch));
        pushButton_8->setIcon(icon);

        gridLayout->addWidget(pushButton_8, 9, 0, 1, 1);

        pushButton_6 = new QPushButton(WidgetFunctional);
        pushButton_6->setObjectName("pushButton_6");
        sizePolicy.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy);
        pushButton_6->setMaximumSize(QSize(60, 60));
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::MailMarkRead));
        pushButton_6->setIcon(icon1);

        gridLayout->addWidget(pushButton_6, 5, 0, 1, 1);

        pushButton_1 = new QPushButton(WidgetFunctional);
        pushButton_1->setObjectName("pushButton_1");
        sizePolicy.setHeightForWidth(pushButton_1->sizePolicy().hasHeightForWidth());
        pushButton_1->setSizePolicy(sizePolicy);
        pushButton_1->setMinimumSize(QSize(60, 60));
        pushButton_1->setMaximumSize(QSize(60, 60));
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::FolderOpen));
        pushButton_1->setIcon(icon2);

        gridLayout->addWidget(pushButton_1, 0, 0, 1, 1);

        pushButton_4 = new QPushButton(WidgetFunctional);
        pushButton_4->setObjectName("pushButton_4");
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);
        pushButton_4->setMinimumSize(QSize(60, 60));
        pushButton_4->setMaximumSize(QSize(60, 60));
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::NetworkOffline));
        pushButton_4->setIcon(icon3);

        gridLayout->addWidget(pushButton_4, 3, 0, 1, 1);

        pushButton_7 = new QPushButton(WidgetFunctional);
        pushButton_7->setObjectName("pushButton_7");
        sizePolicy.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy);
        pushButton_7->setMaximumSize(QSize(60, 60));
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::ContactNew));
        pushButton_7->setIcon(icon4);

        gridLayout->addWidget(pushButton_7, 8, 0, 1, 1);

        pushButton_5 = new QPushButton(WidgetFunctional);
        pushButton_5->setObjectName("pushButton_5");
        sizePolicy.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy);
        pushButton_5->setMaximumSize(QSize(60, 60));
        QIcon icon5(QIcon::fromTheme(QIcon::ThemeIcon::MailMessageNew));
        pushButton_5->setIcon(icon5);

        gridLayout->addWidget(pushButton_5, 4, 0, 1, 1);

        pushButton_2 = new QPushButton(WidgetFunctional);
        pushButton_2->setObjectName("pushButton_2");
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setMinimumSize(QSize(60, 60));
        pushButton_2->setMaximumSize(QSize(60, 60));
        QIcon icon6(QIcon::fromTheme(QIcon::ThemeIcon::EditCopy));
        pushButton_2->setIcon(icon6);

        gridLayout->addWidget(pushButton_2, 1, 0, 1, 1);

        pushButton_3 = new QPushButton(WidgetFunctional);
        pushButton_3->setObjectName("pushButton_3");
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);
        pushButton_3->setMinimumSize(QSize(60, 60));
        pushButton_3->setMaximumSize(QSize(60, 60));
        QIcon icon7(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpenRecent));
        pushButton_3->setIcon(icon7);

        gridLayout->addWidget(pushButton_3, 2, 0, 1, 1);

        pushButton_9 = new QPushButton(WidgetFunctional);
        pushButton_9->setObjectName("pushButton_9");
        sizePolicy.setHeightForWidth(pushButton_9->sizePolicy().hasHeightForWidth());
        pushButton_9->setSizePolicy(sizePolicy);
        pushButton_9->setMaximumSize(QSize(60, 60));
        QIcon icon8(QIcon::fromTheme(QString::fromUtf8("edit-paste")));
        pushButton_9->setIcon(icon8);

        gridLayout->addWidget(pushButton_9, 10, 0, 1, 1);

        QWidget::setTabOrder(pushButton_1, pushButton_2);
        QWidget::setTabOrder(pushButton_2, pushButton_3);
        QWidget::setTabOrder(pushButton_3, pushButton_4);
        QWidget::setTabOrder(pushButton_4, pushButton_5);
        QWidget::setTabOrder(pushButton_5, pushButton_6);
        QWidget::setTabOrder(pushButton_6, pushButton_7);
        QWidget::setTabOrder(pushButton_7, pushButton_8);

        retranslateUi(WidgetFunctional);

        QMetaObject::connectSlotsByName(WidgetFunctional);
    } // setupUi

    void retranslateUi(QWidget *WidgetFunctional)
    {
        WidgetFunctional->setWindowTitle(QCoreApplication::translate("WidgetFunctional", "Form", nullptr));
        pushButton_8->setText(QCoreApplication::translate("WidgetFunctional", "\346\233\264\345\244\232\n"
"\345\212\237\350\203\275", nullptr));
        pushButton_6->setText(QCoreApplication::translate("WidgetFunctional", "\351\202\256\344\273\266\n"
"\346\234\215\345\212\241", nullptr));
        pushButton_1->setText(QCoreApplication::translate("WidgetFunctional", "\346\226\207\344\273\266\n"
"\346\240\207\347\255\276", nullptr));
        pushButton_4->setText(QCoreApplication::translate("WidgetFunctional", "\345\234\250\347\272\277\n"
"\346\226\207\346\241\243", nullptr));
        pushButton_7->setText(QCoreApplication::translate("WidgetFunctional", "\347\224\250\346\210\267\n"
"\347\231\273\345\275\225", nullptr));
        pushButton_5->setText(QCoreApplication::translate("WidgetFunctional", "\346\211\213\345\206\231\n"
"\347\273\230\345\233\276", nullptr));
        pushButton_2->setText(QCoreApplication::translate("WidgetFunctional", "\346\226\207\344\273\266\n"
"\345\244\207\344\273\275", nullptr));
        pushButton_3->setText(QCoreApplication::translate("WidgetFunctional", "\345\244\207\345\277\230\n"
"\346\227\245\347\250\213", nullptr));
        pushButton_9->setText(QCoreApplication::translate("WidgetFunctional", "\345\211\252\345\210\207\n"
"\345\255\227\346\235\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetFunctional: public Ui_WidgetFunctional {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETFUNCTIONAL_H
