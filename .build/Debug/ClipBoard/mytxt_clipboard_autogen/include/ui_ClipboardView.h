/********************************************************************************
** Form generated from reading UI file 'ClipboardView.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIPBOARDVIEW_H
#define UI_CLIPBOARDVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClipboardView
{
public:
    QGridLayout *gridLayout;
    QPushButton *clearButton;
    QPushButton *saveButton;
    QListWidget *listWidget;

    void setupUi(QWidget *ClipboardView)
    {
        if (ClipboardView->objectName().isEmpty())
            ClipboardView->setObjectName("ClipboardView");
        ClipboardView->resize(400, 333);
        gridLayout = new QGridLayout(ClipboardView);
        gridLayout->setObjectName("gridLayout");
        clearButton = new QPushButton(ClipboardView);
        clearButton->setObjectName("clearButton");

        gridLayout->addWidget(clearButton, 1, 0, 1, 1);

        saveButton = new QPushButton(ClipboardView);
        saveButton->setObjectName("saveButton");

        gridLayout->addWidget(saveButton, 1, 1, 1, 1);

        listWidget = new QListWidget(ClipboardView);
        listWidget->setObjectName("listWidget");

        gridLayout->addWidget(listWidget, 0, 0, 1, 2);


        retranslateUi(ClipboardView);

        QMetaObject::connectSlotsByName(ClipboardView);
    } // setupUi

    void retranslateUi(QWidget *ClipboardView)
    {
        ClipboardView->setWindowTitle(QCoreApplication::translate("ClipboardView", "Form", nullptr));
        clearButton->setText(QCoreApplication::translate("ClipboardView", "\346\270\205\347\251\272", nullptr));
        saveButton->setText(QCoreApplication::translate("ClipboardView", "\344\277\235\345\255\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClipboardView: public Ui_ClipboardView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIPBOARDVIEW_H
