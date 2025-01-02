/********************************************************************************
** Form generated from reading UI file 'TagDetail.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAGDETAIL_H
#define UI_TAGDETAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TagDetail
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QPushButton *choosePathBtn;
    QPushButton *YesBtn;
    QPushButton *deleteBtn;

    void setupUi(QWidget *TagDetail)
    {
        if (TagDetail->objectName().isEmpty())
            TagDetail->setObjectName("TagDetail");
        TagDetail->resize(400, 300);
        gridLayout = new QGridLayout(TagDetail);
        gridLayout->setObjectName("gridLayout");
        tableWidget = new QTableWidget(TagDetail);
        tableWidget->setObjectName("tableWidget");

        gridLayout->addWidget(tableWidget, 0, 0, 1, 3);

        choosePathBtn = new QPushButton(TagDetail);
        choosePathBtn->setObjectName("choosePathBtn");

        gridLayout->addWidget(choosePathBtn, 1, 0, 1, 1);

        YesBtn = new QPushButton(TagDetail);
        YesBtn->setObjectName("YesBtn");

        gridLayout->addWidget(YesBtn, 1, 1, 1, 1);

        deleteBtn = new QPushButton(TagDetail);
        deleteBtn->setObjectName("deleteBtn");

        gridLayout->addWidget(deleteBtn, 1, 2, 1, 1);


        retranslateUi(TagDetail);

        QMetaObject::connectSlotsByName(TagDetail);
    } // setupUi

    void retranslateUi(QWidget *TagDetail)
    {
        TagDetail->setWindowTitle(QCoreApplication::translate("TagDetail", "\346\226\207\344\273\266\346\240\207\347\255\276\350\257\246\346\203\205", nullptr));
        choosePathBtn->setText(QCoreApplication::translate("TagDetail", "\351\200\211\345\217\226\350\267\257\345\276\204", nullptr));
        YesBtn->setText(QCoreApplication::translate("TagDetail", "\347\241\256\345\256\236\344\277\256\346\224\271", nullptr));
        deleteBtn->setText(QCoreApplication::translate("TagDetail", "\345\210\240\351\231\244\346\240\207\347\255\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TagDetail: public Ui_TagDetail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAGDETAIL_H
