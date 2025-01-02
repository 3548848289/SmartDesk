/********************************************************************************
** Form generated from reading UI file 'ControlWidTXT.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLWIDTXT_H
#define UI_CONTROLWIDTXT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlWidTXT
{
public:
    QGridLayout *gridLayout;
    QLabel *label;

    void setupUi(QWidget *ControlWidTXT)
    {
        if (ControlWidTXT->objectName().isEmpty())
            ControlWidTXT->setObjectName("ControlWidTXT");
        ControlWidTXT->resize(222, 70);
        gridLayout = new QGridLayout(ControlWidTXT);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(ControlWidTXT);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(ControlWidTXT);

        QMetaObject::connectSlotsByName(ControlWidTXT);
    } // setupUi

    void retranslateUi(QWidget *ControlWidTXT)
    {
        ControlWidTXT->setWindowTitle(QCoreApplication::translate("ControlWidTXT", "Form", nullptr));
        label->setText(QCoreApplication::translate("ControlWidTXT", "\346\265\213\350\257\225\346\226\207\346\234\254", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ControlWidTXT: public Ui_ControlWidTXT {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLWIDTXT_H
