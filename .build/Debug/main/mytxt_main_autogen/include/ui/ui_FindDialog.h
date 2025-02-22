/********************************************************************************
** Form generated from reading UI file 'FindDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDDIALOG_H
#define UI_FINDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FindDialog
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QCheckBox *caseCheckBox;
    QCheckBox *backwardCheckBox;
    QPushButton *findButton;
    QPushButton *findAllButton;

    void setupUi(QDialog *FindDialog)
    {
        if (FindDialog->objectName().isEmpty())
            FindDialog->setObjectName("FindDialog");
        FindDialog->resize(281, 143);
        label = new QLabel(FindDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 10, 51, 21));
        lineEdit = new QLineEdit(FindDialog);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(140, 10, 111, 21));
        caseCheckBox = new QCheckBox(FindDialog);
        caseCheckBox->setObjectName("caseCheckBox");
        caseCheckBox->setGeometry(QRect(10, 60, 91, 20));
        backwardCheckBox = new QCheckBox(FindDialog);
        backwardCheckBox->setObjectName("backwardCheckBox");
        backwardCheckBox->setGeometry(QRect(10, 100, 91, 21));
        findButton = new QPushButton(FindDialog);
        findButton->setObjectName("findButton");
        findButton->setGeometry(QRect(140, 50, 61, 31));
        findAllButton = new QPushButton(FindDialog);
        findAllButton->setObjectName("findAllButton");
        findAllButton->setGeometry(QRect(140, 100, 61, 31));

        retranslateUi(FindDialog);

        findButton->setDefault(false);


        QMetaObject::connectSlotsByName(FindDialog);
    } // setupUi

    void retranslateUi(QDialog *FindDialog)
    {
        FindDialog->setWindowTitle(QCoreApplication::translate("FindDialog", "\346\237\245\346\211\276", nullptr));
        label->setText(QCoreApplication::translate("FindDialog", "\346\237\245\346\211\276\345\206\205\345\256\271\357\274\232", nullptr));
        caseCheckBox->setText(QCoreApplication::translate("FindDialog", "\345\214\271\351\205\215\345\244\247\345\260\217\345\206\231", nullptr));
        backwardCheckBox->setText(QCoreApplication::translate("FindDialog", "\345\217\215\345\220\221\346\237\245\346\211\276", nullptr));
        findButton->setText(QCoreApplication::translate("FindDialog", "\346\237\245\346\211\276", nullptr));
        findAllButton->setText(QCoreApplication::translate("FindDialog", "\346\237\245\346\211\276\346\211\200\346\234\211", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindDialog: public Ui_FindDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDDIALOG_H
