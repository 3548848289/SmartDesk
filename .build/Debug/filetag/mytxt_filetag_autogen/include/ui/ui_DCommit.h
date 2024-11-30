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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DCommit
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_name;
    QLabel *label_path;
    QLineEdit *edit_name;
    QLineEdit *edit_path;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *save;
    QSpacerItem *horizontalSpacer;
    QPushButton *canle;

    void setupUi(QDialog *DCommit)
    {
        if (DCommit->objectName().isEmpty())
            DCommit->setObjectName("DCommit");
        DCommit->resize(319, 222);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::EditCopy));
        DCommit->setWindowIcon(icon);
        gridLayoutWidget = new QWidget(DCommit);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(0, 0, 311, 181));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_name = new QLabel(gridLayoutWidget);
        label_name->setObjectName("label_name");

        gridLayout->addWidget(label_name, 0, 0, 1, 1);

        label_path = new QLabel(gridLayoutWidget);
        label_path->setObjectName("label_path");

        gridLayout->addWidget(label_path, 1, 0, 1, 1);

        edit_name = new QLineEdit(gridLayoutWidget);
        edit_name->setObjectName("edit_name");

        gridLayout->addWidget(edit_name, 0, 1, 1, 1);

        edit_path = new QLineEdit(gridLayoutWidget);
        edit_path->setObjectName("edit_path");

        gridLayout->addWidget(edit_path, 1, 1, 1, 1);

        horizontalLayoutWidget = new QWidget(DCommit);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(50, 190, 221, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        save = new QPushButton(horizontalLayoutWidget);
        save->setObjectName("save");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(save->sizePolicy().hasHeightForWidth());
        save->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(save);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        canle = new QPushButton(horizontalLayoutWidget);
        canle->setObjectName("canle");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(canle->sizePolicy().hasHeightForWidth());
        canle->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(canle);

        horizontalLayout->setStretch(1, 2);
        horizontalLayout->setStretch(2, 1);

        retranslateUi(DCommit);

        QMetaObject::connectSlotsByName(DCommit);
    } // setupUi

    void retranslateUi(QDialog *DCommit)
    {
        DCommit->setWindowTitle(QCoreApplication::translate("DCommit", "\346\226\207\344\273\266\345\244\207\344\273\275", nullptr));
        label_name->setText(QCoreApplication::translate("DCommit", "\346\226\207\344\273\266\345\220\215", nullptr));
        label_path->setText(QCoreApplication::translate("DCommit", "\344\277\235\345\255\230\347\232\204\350\267\257\345\276\204", nullptr));
        edit_name->setText(QString());
        save->setText(QCoreApplication::translate("DCommit", "\344\277\235\345\255\230", nullptr));
        canle->setText(QCoreApplication::translate("DCommit", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DCommit: public Ui_DCommit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DCOMMIT_H
