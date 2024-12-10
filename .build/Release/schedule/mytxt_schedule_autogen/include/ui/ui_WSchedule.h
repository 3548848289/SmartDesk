/********************************************************************************
** Form generated from reading UI file 'WSchedule.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WSCHEDULE_H
#define UI_WSCHEDULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WSchedule
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLineEdit *searchLineEdit;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QLabel *label;
    QPushButton *pushButton;
    QListWidget *listWidget;

    void setupUi(QWidget *WSchedule)
    {
        if (WSchedule->objectName().isEmpty())
            WSchedule->setObjectName("WSchedule");
        WSchedule->resize(256, 368);
        gridLayout = new QGridLayout(WSchedule);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        searchLineEdit = new QLineEdit(WSchedule);
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
        comboBox = new QComboBox(WSchedule);
        comboBox->setObjectName("comboBox");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(comboBox);

        label = new QLabel(WSchedule);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        pushButton = new QPushButton(WSchedule);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 4);
        horizontalLayout->setStretch(2, 4);

        verticalLayout->addLayout(horizontalLayout);

        listWidget = new QListWidget(WSchedule);
        listWidget->setObjectName("listWidget");

        verticalLayout->addWidget(listWidget);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 14);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(WSchedule);

        QMetaObject::connectSlotsByName(WSchedule);
    } // setupUi

    void retranslateUi(QWidget *WSchedule)
    {
        WSchedule->setWindowTitle(QString());
        searchLineEdit->setText(QString());
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("WSchedule", "\346\220\234\347\264\242\346\226\207\344\273\266", nullptr));
        label->setText(QCoreApplication::translate("WSchedule", "\346\226\207\344\273\266\344\275\215\347\275\256", nullptr));
        pushButton->setText(QCoreApplication::translate("WSchedule", "\345\210\260\346\234\237\346\227\266\351\227\264\346\216\222\345\272\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WSchedule: public Ui_WSchedule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WSCHEDULE_H
