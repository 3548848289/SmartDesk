/********************************************************************************
** Form generated from reading UI file 'WOnlineDoc.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WONLINEDOC_H
#define UI_WONLINEDOC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WOnlineDoc
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;

    void setupUi(QWidget *WOnlineDoc)
    {
        if (WOnlineDoc->objectName().isEmpty())
            WOnlineDoc->setObjectName("WOnlineDoc");
        WOnlineDoc->resize(250, 330);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WOnlineDoc->sizePolicy().hasHeightForWidth());
        WOnlineDoc->setSizePolicy(sizePolicy);
        WOnlineDoc->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(WOnlineDoc);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(WOnlineDoc);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setStyleSheet(QString::fromUtf8(""));
        tabWidget->setTabPosition(QTabWidget::TabPosition::North);

        gridLayout->addWidget(tabWidget, 0, 0, 2, 2);


        retranslateUi(WOnlineDoc);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(WOnlineDoc);
    } // setupUi

    void retranslateUi(QWidget *WOnlineDoc)
    {
        WOnlineDoc->setWindowTitle(QCoreApplication::translate("WOnlineDoc", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WOnlineDoc: public Ui_WOnlineDoc {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WONLINEDOC_H
