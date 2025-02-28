/********************************************************************************
** Form generated from reading UI file 'ControlWidCSV.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLWIDCSV_H
#define UI_CONTROLWIDCSV_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlWidCSV
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *deleteColumnButton;
    QPushButton *addColumnButton;
    QPushButton *deleteRowButton;
    QPushButton *addRowButton;
    QPushButton *filterButton;
    QPushButton *sortButton;

    void setupUi(QWidget *ControlWidCSV)
    {
        if (ControlWidCSV->objectName().isEmpty())
            ControlWidCSV->setObjectName("ControlWidCSV");
        ControlWidCSV->resize(326, 100);
        gridLayout_2 = new QGridLayout(ControlWidCSV);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(34);
        gridLayout->setVerticalSpacing(12);
        deleteColumnButton = new QPushButton(ControlWidCSV);
        deleteColumnButton->setObjectName("deleteColumnButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(deleteColumnButton->sizePolicy().hasHeightForWidth());
        deleteColumnButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(deleteColumnButton, 1, 1, 1, 1);

        addColumnButton = new QPushButton(ControlWidCSV);
        addColumnButton->setObjectName("addColumnButton");
        sizePolicy.setHeightForWidth(addColumnButton->sizePolicy().hasHeightForWidth());
        addColumnButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(addColumnButton, 0, 1, 1, 1);

        deleteRowButton = new QPushButton(ControlWidCSV);
        deleteRowButton->setObjectName("deleteRowButton");
        sizePolicy.setHeightForWidth(deleteRowButton->sizePolicy().hasHeightForWidth());
        deleteRowButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(deleteRowButton, 1, 0, 1, 1);

        addRowButton = new QPushButton(ControlWidCSV);
        addRowButton->setObjectName("addRowButton");
        sizePolicy.setHeightForWidth(addRowButton->sizePolicy().hasHeightForWidth());
        addRowButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(addRowButton, 0, 0, 1, 1);

        filterButton = new QPushButton(ControlWidCSV);
        filterButton->setObjectName("filterButton");
        sizePolicy.setHeightForWidth(filterButton->sizePolicy().hasHeightForWidth());
        filterButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(filterButton, 0, 2, 1, 1);

        sortButton = new QPushButton(ControlWidCSV);
        sortButton->setObjectName("sortButton");
        sizePolicy.setHeightForWidth(sortButton->sizePolicy().hasHeightForWidth());
        sortButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(sortButton, 1, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        QWidget::setTabOrder(addRowButton, deleteRowButton);
        QWidget::setTabOrder(deleteRowButton, addColumnButton);
        QWidget::setTabOrder(addColumnButton, deleteColumnButton);
        QWidget::setTabOrder(deleteColumnButton, filterButton);
        QWidget::setTabOrder(filterButton, sortButton);

        retranslateUi(ControlWidCSV);

        QMetaObject::connectSlotsByName(ControlWidCSV);
    } // setupUi

    void retranslateUi(QWidget *ControlWidCSV)
    {
        ControlWidCSV->setWindowTitle(QCoreApplication::translate("ControlWidCSV", "Form", nullptr));
        deleteColumnButton->setText(QCoreApplication::translate("ControlWidCSV", "\345\210\240\351\231\244\345\210\227", nullptr));
        addColumnButton->setText(QCoreApplication::translate("ControlWidCSV", "\345\242\236\345\212\240\345\210\227", nullptr));
        deleteRowButton->setText(QCoreApplication::translate("ControlWidCSV", "\345\210\240\351\231\244\350\241\214", nullptr));
        addRowButton->setText(QCoreApplication::translate("ControlWidCSV", "\345\242\236\345\212\240\350\241\214", nullptr));
        filterButton->setText(QCoreApplication::translate("ControlWidCSV", "\350\277\207\346\273\244", nullptr));
        sortButton->setText(QCoreApplication::translate("ControlWidCSV", "\346\216\222\345\272\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ControlWidCSV: public Ui_ControlWidCSV {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLWIDCSV_H
