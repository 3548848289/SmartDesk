/********************************************************************************
** Form generated from reading UI file 'MoreFunction.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOREFUNCTION_H
#define UI_MOREFUNCTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MoreFunction
{
public:
    QLabel *label;
    QLineEdit *lineEdit;

    void setupUi(QWidget *MoreFunction)
    {
        if (MoreFunction->objectName().isEmpty())
            MoreFunction->setObjectName("MoreFunction");
        MoreFunction->resize(400, 300);
        label = new QLabel(MoreFunction);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 30, 71, 31));
        lineEdit = new QLineEdit(MoreFunction);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(80, 40, 271, 20));

        retranslateUi(MoreFunction);

        QMetaObject::connectSlotsByName(MoreFunction);
    } // setupUi

    void retranslateUi(QWidget *MoreFunction)
    {
        MoreFunction->setWindowTitle(QCoreApplication::translate("MoreFunction", "Form", nullptr));
        label->setText(QCoreApplication::translate("MoreFunction", "github\345\234\260\345\235\200", nullptr));
        lineEdit->setText(QCoreApplication::translate("MoreFunction", "https://github.com/3548848289/SmartDesk", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MoreFunction: public Ui_MoreFunction {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOREFUNCTION_H
