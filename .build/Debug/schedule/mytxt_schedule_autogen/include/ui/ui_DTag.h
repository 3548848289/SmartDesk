/********************************************************************************
** Form generated from reading UI file 'DTag.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DTAG_H
#define UI_DTAG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DTag
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout;
    QLabel *label_1;
    QLabel *label_3;
    QDateTimeEdit *dateTimeEdit;
    QTextEdit *annotationTextEdit;
    QLabel *label_2;
    QLineEdit *tagsLineEdit;
    QPushButton *saveButton;

    void setupUi(QDialog *DTag)
    {
        if (DTag->objectName().isEmpty())
            DTag->setObjectName("DTag");
        DTag->resize(359, 276);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/usedimage/tag.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        DTag->setWindowIcon(icon);
        layoutWidget = new QWidget(DTag);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 10, 344, 255));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_1 = new QLabel(layoutWidget);
        label_1->setObjectName("label_1");
        label_1->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_1, 0, 0, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/usedimage/edittag.svg")));
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        dateTimeEdit = new QDateTimeEdit(layoutWidget);
        dateTimeEdit->setObjectName("dateTimeEdit");

        gridLayout->addWidget(dateTimeEdit, 1, 1, 1, 1);

        annotationTextEdit = new QTextEdit(layoutWidget);
        annotationTextEdit->setObjectName("annotationTextEdit");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(annotationTextEdit->sizePolicy().hasHeightForWidth());
        annotationTextEdit->setSizePolicy(sizePolicy);

        gridLayout->addWidget(annotationTextEdit, 2, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        tagsLineEdit = new QLineEdit(layoutWidget);
        tagsLineEdit->setObjectName("tagsLineEdit");

        gridLayout->addWidget(tagsLineEdit, 0, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);

        saveButton = new QPushButton(layoutWidget);
        saveButton->setObjectName("saveButton");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(saveButton->sizePolicy().hasHeightForWidth());
        saveButton->setSizePolicy(sizePolicy1);
        saveButton->setStyleSheet(QString::fromUtf8(" /*\n"
"\n"
"QPushButton {\n"
"    color: #7598db;  \n"
"    background-color: #e0e0e0;  \n"
"    border: 1px solid #ccc; \n"
"    border-radius: 5px;\n"
"    padding: 5px 10px;\n"
"}\n"
"*/\n"
""));

        horizontalLayout_2->addWidget(saveButton);


        retranslateUi(DTag);

        QMetaObject::connectSlotsByName(DTag);
    } // setupUi

    void retranslateUi(QDialog *DTag)
    {
        DTag->setWindowTitle(QCoreApplication::translate("DTag", "\346\226\260\345\242\236\345\244\207\345\277\230\346\226\207\344\273\266", nullptr));
        label_1->setText(QCoreApplication::translate("DTag", "\346\226\207\344\273\266", nullptr));
        label_3->setText(QCoreApplication::translate("DTag", "\345\244\207\346\263\250", nullptr));
        label_2->setText(QCoreApplication::translate("DTag", "\346\227\245\346\234\237", nullptr));
        saveButton->setText(QCoreApplication::translate("DTag", "\344\277\235\345\255\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DTag: public Ui_DTag {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DTAG_H
