/********************************************************************************
** Form generated from reading UI file 'FileSystem.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILESYSTEM_H
#define UI_FILESYSTEM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileSystem
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *pathLineEdit;
    QPushButton *goButton;
    QTreeView *treeView;

    void setupUi(QWidget *FileSystem)
    {
        if (FileSystem->objectName().isEmpty())
            FileSystem->setObjectName("FileSystem");
        FileSystem->resize(391, 593);
        FileSystem->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(FileSystem);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        pathLineEdit = new QLineEdit(FileSystem);
        pathLineEdit->setObjectName("pathLineEdit");
        pathLineEdit->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pathLineEdit->sizePolicy().hasHeightForWidth());
        pathLineEdit->setSizePolicy(sizePolicy);
        pathLineEdit->setBaseSize(QSize(0, 13));

        horizontalLayout->addWidget(pathLineEdit);

        goButton = new QPushButton(FileSystem);
        goButton->setObjectName("goButton");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(goButton->sizePolicy().hasHeightForWidth());
        goButton->setSizePolicy(sizePolicy1);
        goButton->setStyleSheet(QString::fromUtf8("/* \n"
"QPushButton {\n"
"    color: #7598db;  \n"
"    background-color: #e0e0e0;  \n"
"    border: 1px solid #ccc; \n"
"    border-radius: 5px;  \n"
"    padding: 5px 10px;  \n"
"}\n"
"*/"));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::GoUp));
        goButton->setIcon(icon);
        goButton->setIconSize(QSize(10, 10));

        horizontalLayout->addWidget(goButton);

        horizontalLayout->setStretch(0, 7);
        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        treeView = new QTreeView(FileSystem);
        treeView->setObjectName("treeView");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(treeView);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 13);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(FileSystem);

        QMetaObject::connectSlotsByName(FileSystem);
    } // setupUi

    void retranslateUi(QWidget *FileSystem)
    {
        FileSystem->setWindowTitle(QCoreApplication::translate("FileSystem", "Form", nullptr));
        goButton->setText(QCoreApplication::translate("FileSystem", "\346\233\264\346\224\271\n"
"\350\267\257\345\276\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileSystem: public Ui_FileSystem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILESYSTEM_H
