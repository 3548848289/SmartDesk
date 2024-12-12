/********************************************************************************
** Form generated from reading UI file 'FileItemWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEITEMWIDGET_H
#define UI_FILEITEMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileItemWidget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *tagLabel;
    QVBoxLayout *verticalLayout_6;
    QLabel *fileLabel;
    QLabel *pathLabel;
    QVBoxLayout *verticalLayout_2;
    QLabel *expirationLabel;

    void setupUi(QWidget *FileItemWidget)
    {
        if (FileItemWidget->objectName().isEmpty())
            FileItemWidget->setObjectName("FileItemWidget");
        FileItemWidget->resize(409, 160);
        gridLayout = new QGridLayout(FileItemWidget);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        tagLabel = new QLabel(FileItemWidget);
        tagLabel->setObjectName("tagLabel");
        tagLabel->setPixmap(QPixmap(QString::fromUtf8(":/usedimage/tag.svg")));

        horizontalLayout->addWidget(tagLabel);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        fileLabel = new QLabel(FileItemWidget);
        fileLabel->setObjectName("fileLabel");
        QFont font;
        font.setPointSize(12);
        fileLabel->setFont(font);
        fileLabel->setStyleSheet(QString::fromUtf8("QLabel { color: #DB00FF }"));

        verticalLayout_6->addWidget(fileLabel);

        pathLabel = new QLabel(FileItemWidget);
        pathLabel->setObjectName("pathLabel");
        QFont font1;
        font1.setPointSize(7);
        pathLabel->setFont(font1);

        verticalLayout_6->addWidget(pathLabel);

        verticalLayout_6->setStretch(0, 4);
        verticalLayout_6->setStretch(1, 2);

        horizontalLayout->addLayout(verticalLayout_6);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        expirationLabel = new QLabel(FileItemWidget);
        expirationLabel->setObjectName("expirationLabel");

        verticalLayout_2->addWidget(expirationLabel);

        verticalLayout_2->setStretch(0, 8);

        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 4);
        horizontalLayout->setStretch(2, 4);

        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(FileItemWidget);

        QMetaObject::connectSlotsByName(FileItemWidget);
    } // setupUi

    void retranslateUi(QWidget *FileItemWidget)
    {
        FileItemWidget->setWindowTitle(QString());
        tagLabel->setText(QString());
        fileLabel->setText(QCoreApplication::translate("FileItemWidget", "TextLabel", nullptr));
        pathLabel->setText(QCoreApplication::translate("FileItemWidget", "TextLabel", nullptr));
        expirationLabel->setText(QCoreApplication::translate("FileItemWidget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileItemWidget: public Ui_FileItemWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEITEMWIDGET_H
