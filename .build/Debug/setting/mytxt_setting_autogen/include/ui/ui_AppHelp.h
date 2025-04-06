/********************************************************************************
** Form generated from reading UI file 'AppHelp.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPHELP_H
#define UI_APPHELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AppHelp
{
public:

    void setupUi(QWidget *AppHelp)
    {
        if (AppHelp->objectName().isEmpty())
            AppHelp->setObjectName("AppHelp");
        AppHelp->resize(400, 300);

        retranslateUi(AppHelp);

        QMetaObject::connectSlotsByName(AppHelp);
    } // setupUi

    void retranslateUi(QWidget *AppHelp)
    {
        AppHelp->setWindowTitle(QCoreApplication::translate("AppHelp", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AppHelp: public Ui_AppHelp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPHELP_H
