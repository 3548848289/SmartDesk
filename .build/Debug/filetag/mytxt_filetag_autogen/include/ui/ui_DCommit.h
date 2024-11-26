/********************************************************************************
** Form generated from reading UI file 'DCommit.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DCOMMIT_H
#define UI_DCOMMIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DCommit
{
public:
    QLineEdit *edit_path;
    QLabel *label_path;
    QLineEdit *edit_name;
    QLabel *label_name;
    QPushButton *save;
    QPushButton *canle;

    void setupUi(QDialog *DCommit)
    {
        if (DCommit->objectName().isEmpty())
            DCommit->setObjectName("DCommit");
        DCommit->resize(319, 222);
        edit_path = new QLineEdit(DCommit);
        edit_path->setObjectName("edit_path");
        edit_path->setGeometry(QRect(160, 70, 113, 20));
        label_path = new QLabel(DCommit);
        label_path->setObjectName("label_path");
        label_path->setGeometry(QRect(30, 70, 71, 21));
        edit_name = new QLineEdit(DCommit);
        edit_name->setObjectName("edit_name");
        edit_name->setGeometry(QRect(160, 30, 113, 20));
        label_name = new QLabel(DCommit);
        label_name->setObjectName("label_name");
        label_name->setGeometry(QRect(30, 30, 71, 21));
        save = new QPushButton(DCommit);
        save->setObjectName("save");
        save->setGeometry(QRect(30, 140, 51, 31));
        canle = new QPushButton(DCommit);
        canle->setObjectName("canle");
        canle->setGeometry(QRect(160, 140, 51, 31));

        retranslateUi(DCommit);

        QMetaObject::connectSlotsByName(DCommit);
    } // setupUi

    void retranslateUi(QDialog *DCommit)
    {
        DCommit->setWindowTitle(QCoreApplication::translate("DCommit", "Dialog", nullptr));
        label_path->setText(QCoreApplication::translate("DCommit", "\344\277\235\345\255\230\347\232\204\350\267\257\345\276\204", nullptr));
        edit_name->setText(QString());
        label_name->setText(QCoreApplication::translate("DCommit", "\346\226\207\344\273\266\345\220\215", nullptr));
        save->setText(QCoreApplication::translate("DCommit", "\344\277\235\345\255\230", nullptr));
        canle->setText(QCoreApplication::translate("DCommit", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DCommit: public Ui_DCommit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DCOMMIT_H
