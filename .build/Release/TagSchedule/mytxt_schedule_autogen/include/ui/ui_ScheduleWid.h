/********************************************************************************
** Form generated from reading UI file 'ScheduleWid.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHEDULEWID_H
#define UI_SCHEDULEWID_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScheduleWid
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLineEdit *searchLineEdit;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QLabel *label;
    QLabel *label_2;
    QWidget *widget;
    QListWidget *listWidget;
    QComboBox *sortComboBox;

    void setupUi(QWidget *ScheduleWid)
    {
        if (ScheduleWid->objectName().isEmpty())
            ScheduleWid->setObjectName("ScheduleWid");
        ScheduleWid->resize(256, 368);
        gridLayout = new QGridLayout(ScheduleWid);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        searchLineEdit = new QLineEdit(ScheduleWid);
        searchLineEdit->setObjectName("searchLineEdit");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(searchLineEdit->sizePolicy().hasHeightForWidth());
        searchLineEdit->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(searchLineEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(6, -1, -1, -1);
        comboBox = new QComboBox(ScheduleWid);
        comboBox->setObjectName("comboBox");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(comboBox);

        label = new QLabel(ScheduleWid);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(ScheduleWid);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        widget = new QWidget(ScheduleWid);
        widget->setObjectName("widget");

        horizontalLayout->addWidget(widget);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 8);
        horizontalLayout->setStretch(2, 4);
        horizontalLayout->setStretch(3, 1);

        verticalLayout->addLayout(horizontalLayout);

        listWidget = new QListWidget(ScheduleWid);
        listWidget->setObjectName("listWidget");

        verticalLayout->addWidget(listWidget);

        sortComboBox = new QComboBox(ScheduleWid);
        sortComboBox->addItem(QString());
        sortComboBox->addItem(QString());
        sortComboBox->setObjectName("sortComboBox");

        verticalLayout->addWidget(sortComboBox);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 14);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        QWidget::setTabOrder(searchLineEdit, comboBox);
        QWidget::setTabOrder(comboBox, listWidget);

        retranslateUi(ScheduleWid);

        QMetaObject::connectSlotsByName(ScheduleWid);
    } // setupUi

    void retranslateUi(QWidget *ScheduleWid)
    {
        ScheduleWid->setWindowTitle(QString());
        searchLineEdit->setText(QString());
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("ScheduleWid", "\346\220\234\347\264\242\346\226\207\344\273\266", nullptr));
        label->setText(QCoreApplication::translate("ScheduleWid", "\346\226\207\344\273\266\344\275\215\347\275\256", nullptr));
        label_2->setText(QCoreApplication::translate("ScheduleWid", "\345\210\260\346\234\237\346\227\266\351\227\264", nullptr));
        sortComboBox->setItemText(0, QCoreApplication::translate("ScheduleWid", "\346\214\211\345\210\260\346\234\237\346\227\266\351\227\264\345\215\207\345\272\217", nullptr));
        sortComboBox->setItemText(1, QCoreApplication::translate("ScheduleWid", "\346\214\211\345\210\260\346\234\237\346\227\266\351\227\264\351\231\215\345\272\217", nullptr));

    } // retranslateUi

};

namespace Ui {
    class ScheduleWid: public Ui_ScheduleWid {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHEDULEWID_H
