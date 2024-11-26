/********************************************************************************
** Form generated from reading UI file 'WFileHis.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WFILEHIS_H
#define UI_WFILEHIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WFileHis
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QListWidget *listWidget;

    void setupUi(QWidget *WFileHis)
    {
        if (WFileHis->objectName().isEmpty())
            WFileHis->setObjectName("WFileHis");
        WFileHis->resize(400, 199);
        gridLayout = new QGridLayout(WFileHis);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(WFileHis);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        listWidget = new QListWidget(WFileHis);
        listWidget->setObjectName("listWidget");

        gridLayout->addWidget(listWidget, 1, 0, 1, 1);


        retranslateUi(WFileHis);

        QMetaObject::connectSlotsByName(WFileHis);
    } // setupUi

    void retranslateUi(QWidget *WFileHis)
    {
        WFileHis->setWindowTitle(QCoreApplication::translate("WFileHis", "Form", nullptr));
        label->setText(QCoreApplication::translate("WFileHis", "\346\226\207\344\273\266\346\217\220\344\272\244\345\216\206\345\217\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WFileHis: public Ui_WFileHis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WFILEHIS_H
