/********************************************************************************
** Form generated from reading UI file 'Setting.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_H
#define UI_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Setting
{
public:
    QTreeWidget *treeWidget;
    QStackedWidget *stackedWidget;
    QWidget *all_setting;
    QCheckBox *enableTrayCheckBox;
    QLabel *label_3;
    QWidget *file_see;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QWidget *email_service;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_3;
    QLabel *label_9;
    QLabel *label_7;
    QLineEdit *lineEdit_4;
    QLabel *label_8;
    QLineEdit *lineEdit_5;
    QLabel *label_6;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label_10;
    QLineEdit *lineEdit_6;
    QLabel *label_11;
    QWidget *file_backup;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEditBackupDir;
    QPushButton *pushButton;
    QWidget *online_doc;
    QLabel *label_4;
    QComboBox *comboBoxReminder;
    QTimeEdit *timeEditReminder;
    QLabel *label_5;

    void setupUi(QWidget *Setting)
    {
        if (Setting->objectName().isEmpty())
            Setting->setObjectName("Setting");
        Setting->resize(524, 380);
        treeWidget = new QTreeWidget(Setting);
        new QTreeWidgetItem(treeWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem2);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        treeWidget->setObjectName("treeWidget");
        treeWidget->setGeometry(QRect(6, 6, 131, 351));
        stackedWidget = new QStackedWidget(Setting);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(182, 6, 321, 341));
        all_setting = new QWidget();
        all_setting->setObjectName("all_setting");
        enableTrayCheckBox = new QCheckBox(all_setting);
        enableTrayCheckBox->setObjectName("enableTrayCheckBox");
        enableTrayCheckBox->setGeometry(QRect(90, 30, 91, 31));
        label_3 = new QLabel(all_setting);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 20, 71, 41));
        stackedWidget->addWidget(all_setting);
        file_see = new QWidget();
        file_see->setObjectName("file_see");
        horizontalLayoutWidget = new QWidget(file_see);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(50, 70, 141, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(label);

        spinBox = new QSpinBox(horizontalLayoutWidget);
        spinBox->setObjectName("spinBox");

        horizontalLayout->addWidget(spinBox);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);
        stackedWidget->addWidget(file_see);
        email_service = new QWidget();
        email_service->setObjectName("email_service");
        gridLayoutWidget = new QWidget(email_service);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(40, 30, 231, 281));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_3 = new QLineEdit(gridLayoutWidget);
        lineEdit_3->setObjectName("lineEdit_3");

        gridLayout->addWidget(lineEdit_3, 2, 1, 1, 1);

        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName("label_9");

        gridLayout->addWidget(label_9, 3, 0, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName("label_7");

        gridLayout->addWidget(label_7, 1, 0, 1, 1);

        lineEdit_4 = new QLineEdit(gridLayoutWidget);
        lineEdit_4->setObjectName("lineEdit_4");

        gridLayout->addWidget(lineEdit_4, 3, 1, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName("label_8");

        gridLayout->addWidget(label_8, 2, 0, 1, 1);

        lineEdit_5 = new QLineEdit(gridLayoutWidget);
        lineEdit_5->setObjectName("lineEdit_5");

        gridLayout->addWidget(lineEdit_5, 4, 1, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        lineEdit = new QLineEdit(gridLayoutWidget);
        lineEdit->setObjectName("lineEdit");

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        lineEdit_2 = new QLineEdit(gridLayoutWidget);
        lineEdit_2->setObjectName("lineEdit_2");

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 1);

        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName("label_10");

        gridLayout->addWidget(label_10, 4, 0, 1, 1);

        lineEdit_6 = new QLineEdit(gridLayoutWidget);
        lineEdit_6->setObjectName("lineEdit_6");

        gridLayout->addWidget(lineEdit_6, 5, 1, 1, 1);

        label_11 = new QLabel(gridLayoutWidget);
        label_11->setObjectName("label_11");

        gridLayout->addWidget(label_11, 5, 0, 1, 1);

        stackedWidget->addWidget(email_service);
        file_backup = new QWidget();
        file_backup->setObjectName("file_backup");
        horizontalLayoutWidget_2 = new QWidget(file_backup);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(10, 20, 321, 61));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget_2);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(label_2);

        lineEditBackupDir = new QLineEdit(horizontalLayoutWidget_2);
        lineEditBackupDir->setObjectName("lineEditBackupDir");

        horizontalLayout_2->addWidget(lineEditBackupDir);

        pushButton = new QPushButton(horizontalLayoutWidget_2);
        pushButton->setObjectName("pushButton");

        horizontalLayout_2->addWidget(pushButton);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 5);
        stackedWidget->addWidget(file_backup);
        online_doc = new QWidget();
        online_doc->setObjectName("online_doc");
        label_4 = new QLabel(online_doc);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 10, 101, 61));
        comboBoxReminder = new QComboBox(online_doc);
        comboBoxReminder->addItem(QString());
        comboBoxReminder->addItem(QString());
        comboBoxReminder->addItem(QString());
        comboBoxReminder->setObjectName("comboBoxReminder");
        comboBoxReminder->setGeometry(QRect(110, 30, 121, 22));
        timeEditReminder = new QTimeEdit(online_doc);
        timeEditReminder->setObjectName("timeEditReminder");
        timeEditReminder->setGeometry(QRect(110, 80, 118, 22));
        label_5 = new QLabel(online_doc);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 60, 101, 61));
        stackedWidget->addWidget(online_doc);

        retranslateUi(Setting);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(Setting);
    } // setupUi

    void retranslateUi(QWidget *Setting)
    {
        Setting->setWindowTitle(QCoreApplication::translate("Setting", "Form", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("Setting", "\350\256\276\347\275\256", nullptr));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("Setting", "\346\200\273\344\275\223\350\256\276\347\275\256", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem2->setText(0, QCoreApplication::translate("Setting", "\346\226\207\344\273\266\346\237\245\347\234\213", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem2->child(0);
        ___qtreewidgetitem3->setText(0, QCoreApplication::translate("Setting", "\345\255\227\344\275\223\345\244\247\345\260\217", nullptr));
        QTreeWidgetItem *___qtreewidgetitem4 = treeWidget->topLevelItem(2);
        ___qtreewidgetitem4->setText(0, QCoreApplication::translate("Setting", "\351\202\256\344\273\266\346\234\215\345\212\241", nullptr));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem4->child(0);
        ___qtreewidgetitem5->setText(0, QCoreApplication::translate("Setting", "\346\224\266\345\217\221\344\272\272", nullptr));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem4->child(1);
        ___qtreewidgetitem6->setText(0, QCoreApplication::translate("Setting", "\350\256\276\347\275\256", nullptr));
        QTreeWidgetItem *___qtreewidgetitem7 = treeWidget->topLevelItem(3);
        ___qtreewidgetitem7->setText(0, QCoreApplication::translate("Setting", "\346\226\207\344\273\266\345\244\207\344\273\275", nullptr));
        QTreeWidgetItem *___qtreewidgetitem8 = ___qtreewidgetitem7->child(0);
        ___qtreewidgetitem8->setText(0, QCoreApplication::translate("Setting", "\345\244\207\344\273\275\350\267\257\345\276\204", nullptr));
        QTreeWidgetItem *___qtreewidgetitem9 = treeWidget->topLevelItem(4);
        ___qtreewidgetitem9->setText(0, QCoreApplication::translate("Setting", "\345\244\207\345\277\230\346\227\245\347\250\213", nullptr));
        QTreeWidgetItem *___qtreewidgetitem10 = ___qtreewidgetitem9->child(0);
        ___qtreewidgetitem10->setText(0, QCoreApplication::translate("Setting", "\345\210\260\346\234\237\346\217\220\351\206\222\346\226\271\345\274\217", nullptr));
        QTreeWidgetItem *___qtreewidgetitem11 = ___qtreewidgetitem9->child(1);
        ___qtreewidgetitem11->setText(0, QCoreApplication::translate("Setting", "\346\217\220\345\211\215\345\244\232\344\271\205\346\217\220\351\206\222", nullptr));
        treeWidget->setSortingEnabled(__sortingEnabled);

        enableTrayCheckBox->setText(QCoreApplication::translate("Setting", "\346\230\257\345\220\246\345\220\257\347\224\250", nullptr));
        label_3->setText(QCoreApplication::translate("Setting", "\346\211\230\347\233\230", nullptr));
        label->setText(QCoreApplication::translate("Setting", "\345\255\227\344\275\223\345\244\247\345\260\217", nullptr));
        label_9->setText(QCoreApplication::translate("Setting", "ssl", nullptr));
        label_7->setText(QCoreApplication::translate("Setting", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_8->setText(QCoreApplication::translate("Setting", "\347\253\257\345\217\243", nullptr));
        label_6->setText(QCoreApplication::translate("Setting", "\346\234\215\345\212\241\345\231\250", nullptr));
        label_10->setText(QCoreApplication::translate("Setting", "\345\217\221\344\273\266\344\272\272", nullptr));
        label_11->setText(QCoreApplication::translate("Setting", "\346\224\266\344\273\266\344\272\272", nullptr));
        label_2->setText(QCoreApplication::translate("Setting", "\347\250\213\345\272\217\n"
"\345\244\207\344\273\275\n"
"\347\233\256\345\275\225", nullptr));
        pushButton->setText(QCoreApplication::translate("Setting", "\351\200\211\345\217\226\n"
"\350\267\257\345\276\204", nullptr));
        label_4->setText(QCoreApplication::translate("Setting", "\346\217\220\351\206\222\346\226\271\345\274\217", nullptr));
        comboBoxReminder->setItemText(0, QCoreApplication::translate("Setting", "\344\270\215\346\217\220\351\206\222", nullptr));
        comboBoxReminder->setItemText(1, QCoreApplication::translate("Setting", "\345\274\271\347\252\227\346\217\220\351\206\222", nullptr));
        comboBoxReminder->setItemText(2, QCoreApplication::translate("Setting", "\351\202\256\344\273\266\346\217\220\351\206\222", nullptr));

        label_5->setText(QCoreApplication::translate("Setting", "\346\217\220\345\211\215\345\244\232\344\271\205\346\217\220\351\206\222", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Setting: public Ui_Setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
