/********************************************************************************
** Form generated from reading UI file 'TagList.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAGLIST_H
#define UI_TAGLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TagList
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *tagLabel;
    QVBoxLayout *verticalLayout_6;
    QLabel *fileLabel;
    QLineEdit *lineEdit;
    QLabel *expirationLabel;
    QPushButton *pushButton;

    void setupUi(QWidget *TagList)
    {
        if (TagList->objectName().isEmpty())
            TagList->setObjectName("TagList");
        TagList->resize(365, 142);
        gridLayout = new QGridLayout(TagList);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        tagLabel = new QLabel(TagList);
        tagLabel->setObjectName("tagLabel");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tagLabel->sizePolicy().hasHeightForWidth());
        tagLabel->setSizePolicy(sizePolicy);
        tagLabel->setMinimumSize(QSize(50, 50));

        horizontalLayout->addWidget(tagLabel);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        fileLabel = new QLabel(TagList);
        fileLabel->setObjectName("fileLabel");
        QFont font;
        font.setPointSize(12);
        fileLabel->setFont(font);
        fileLabel->setStyleSheet(QString::fromUtf8("QLabel { color: #DB00FF }"));

        verticalLayout_6->addWidget(fileLabel);

        lineEdit = new QLineEdit(TagList);
        lineEdit->setObjectName("lineEdit");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);
        lineEdit->setReadOnly(true);

        verticalLayout_6->addWidget(lineEdit);

        verticalLayout_6->setStretch(0, 4);
        verticalLayout_6->setStretch(1, 1);

        horizontalLayout->addLayout(verticalLayout_6);

        expirationLabel = new QLabel(TagList);
        expirationLabel->setObjectName("expirationLabel");

        horizontalLayout->addWidget(expirationLabel);

        pushButton = new QPushButton(TagList);
        pushButton->setObjectName("pushButton");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy2);
        pushButton->setMaximumSize(QSize(30, 30));

        horizontalLayout->addWidget(pushButton);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 8);
        horizontalLayout->setStretch(2, 4);
        horizontalLayout->setStretch(3, 1);

        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(TagList);

        QMetaObject::connectSlotsByName(TagList);
    } // setupUi

    void retranslateUi(QWidget *TagList)
    {
        TagList->setWindowTitle(QString());
        tagLabel->setText(QString());
        fileLabel->setText(QCoreApplication::translate("TagList", "TextLabel", nullptr));
        expirationLabel->setText(QCoreApplication::translate("TagList", "TextLabel", nullptr));
        pushButton->setText(QCoreApplication::translate("TagList", "\350\257\246\346\203\205", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TagList: public Ui_TagList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAGLIST_H
