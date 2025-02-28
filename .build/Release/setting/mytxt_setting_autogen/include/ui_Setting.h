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
#include <QtGui/QIcon>
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
    QCheckBox *all_setting_checkBox;
    QLabel *all_setting_label2;
    QLabel *all_setting_label1;
    QSpinBox *all_setting_spinBox;
    QWidget *file_system;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *file_system_label;
    QLineEdit *file_system_lineEdit;
    QPushButton *file_system_Btn;
    QWidget *file_see;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *file_see_label;
    QSpinBox *file_see_spinBox;
    QWidget *email_service;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *email_service_lineEdit_3;
    QLabel *email_service_label_4;
    QLabel *email_service_label_2;
    QLineEdit *email_service_lineEdit_4;
    QLabel *email_service_label_3;
    QLineEdit *email_service_lineEdit_5;
    QLabel *email_service_label_1;
    QLineEdit *email_service_lineEdit_1;
    QLineEdit *email_service_lineEdit_2;
    QLabel *email_service_label_5;
    QLineEdit *email_service_lineEdit_6;
    QLabel *email_service_label_6;
    QWidget *file_backup;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *file_backup_label;
    QLineEdit *file_backup_lineEdit;
    QPushButton *file_backup_Btn;
    QWidget *online_doc;
    QLabel *online_doc_label1;
    QComboBox *online_doc_comboBox;
    QTimeEdit *online_doc_timeEdit_1;
    QLabel *online_doc_label2;
    QTimeEdit *online_doc_timeEdit_2;
    QLabel *online_doc_label2_2;
    QLabel *label;

    void setupUi(QWidget *Setting)
    {
        if (Setting->objectName().isEmpty())
            Setting->setObjectName("Setting");
        Setting->resize(524, 380);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/png/Settings.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Setting->setWindowIcon(icon);
        treeWidget = new QTreeWidget(Setting);
        new QTreeWidgetItem(treeWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem1);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem3);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        treeWidget->setObjectName("treeWidget");
        treeWidget->setGeometry(QRect(6, 6, 131, 351));
        stackedWidget = new QStackedWidget(Setting);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(182, 6, 321, 341));
        all_setting = new QWidget();
        all_setting->setObjectName("all_setting");
        all_setting_checkBox = new QCheckBox(all_setting);
        all_setting_checkBox->setObjectName("all_setting_checkBox");
        all_setting_checkBox->setGeometry(QRect(100, 130, 91, 31));
        all_setting_label2 = new QLabel(all_setting);
        all_setting_label2->setObjectName("all_setting_label2");
        all_setting_label2->setGeometry(QRect(30, 130, 71, 41));
        all_setting_label1 = new QLabel(all_setting);
        all_setting_label1->setObjectName("all_setting_label1");
        all_setting_label1->setGeometry(QRect(20, 80, 71, 41));
        all_setting_spinBox = new QSpinBox(all_setting);
        all_setting_spinBox->setObjectName("all_setting_spinBox");
        all_setting_spinBox->setGeometry(QRect(100, 90, 101, 22));
        stackedWidget->addWidget(all_setting);
        file_system = new QWidget();
        file_system->setObjectName("file_system");
        horizontalLayoutWidget_3 = new QWidget(file_system);
        horizontalLayoutWidget_3->setObjectName("horizontalLayoutWidget_3");
        horizontalLayoutWidget_3->setGeometry(QRect(10, 40, 281, 61));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        file_system_label = new QLabel(horizontalLayoutWidget_3);
        file_system_label->setObjectName("file_system_label");
        file_system_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_3->addWidget(file_system_label);

        file_system_lineEdit = new QLineEdit(horizontalLayoutWidget_3);
        file_system_lineEdit->setObjectName("file_system_lineEdit");

        horizontalLayout_3->addWidget(file_system_lineEdit);

        file_system_Btn = new QPushButton(horizontalLayoutWidget_3);
        file_system_Btn->setObjectName("file_system_Btn");

        horizontalLayout_3->addWidget(file_system_Btn);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 5);
        stackedWidget->addWidget(file_system);
        file_see = new QWidget();
        file_see->setObjectName("file_see");
        horizontalLayoutWidget = new QWidget(file_see);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(50, 70, 141, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        file_see_label = new QLabel(horizontalLayoutWidget);
        file_see_label->setObjectName("file_see_label");
        file_see_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(file_see_label);

        file_see_spinBox = new QSpinBox(horizontalLayoutWidget);
        file_see_spinBox->setObjectName("file_see_spinBox");

        horizontalLayout->addWidget(file_see_spinBox);

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
        email_service_lineEdit_3 = new QLineEdit(gridLayoutWidget);
        email_service_lineEdit_3->setObjectName("email_service_lineEdit_3");

        gridLayout->addWidget(email_service_lineEdit_3, 2, 1, 1, 1);

        email_service_label_4 = new QLabel(gridLayoutWidget);
        email_service_label_4->setObjectName("email_service_label_4");

        gridLayout->addWidget(email_service_label_4, 3, 0, 1, 1);

        email_service_label_2 = new QLabel(gridLayoutWidget);
        email_service_label_2->setObjectName("email_service_label_2");

        gridLayout->addWidget(email_service_label_2, 1, 0, 1, 1);

        email_service_lineEdit_4 = new QLineEdit(gridLayoutWidget);
        email_service_lineEdit_4->setObjectName("email_service_lineEdit_4");

        gridLayout->addWidget(email_service_lineEdit_4, 3, 1, 1, 1);

        email_service_label_3 = new QLabel(gridLayoutWidget);
        email_service_label_3->setObjectName("email_service_label_3");

        gridLayout->addWidget(email_service_label_3, 2, 0, 1, 1);

        email_service_lineEdit_5 = new QLineEdit(gridLayoutWidget);
        email_service_lineEdit_5->setObjectName("email_service_lineEdit_5");

        gridLayout->addWidget(email_service_lineEdit_5, 4, 1, 1, 1);

        email_service_label_1 = new QLabel(gridLayoutWidget);
        email_service_label_1->setObjectName("email_service_label_1");

        gridLayout->addWidget(email_service_label_1, 0, 0, 1, 1);

        email_service_lineEdit_1 = new QLineEdit(gridLayoutWidget);
        email_service_lineEdit_1->setObjectName("email_service_lineEdit_1");

        gridLayout->addWidget(email_service_lineEdit_1, 0, 1, 1, 1);

        email_service_lineEdit_2 = new QLineEdit(gridLayoutWidget);
        email_service_lineEdit_2->setObjectName("email_service_lineEdit_2");

        gridLayout->addWidget(email_service_lineEdit_2, 1, 1, 1, 1);

        email_service_label_5 = new QLabel(gridLayoutWidget);
        email_service_label_5->setObjectName("email_service_label_5");

        gridLayout->addWidget(email_service_label_5, 4, 0, 1, 1);

        email_service_lineEdit_6 = new QLineEdit(gridLayoutWidget);
        email_service_lineEdit_6->setObjectName("email_service_lineEdit_6");

        gridLayout->addWidget(email_service_lineEdit_6, 5, 1, 1, 1);

        email_service_label_6 = new QLabel(gridLayoutWidget);
        email_service_label_6->setObjectName("email_service_label_6");

        gridLayout->addWidget(email_service_label_6, 5, 0, 1, 1);

        stackedWidget->addWidget(email_service);
        file_backup = new QWidget();
        file_backup->setObjectName("file_backup");
        horizontalLayoutWidget_2 = new QWidget(file_backup);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(10, 20, 321, 61));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        file_backup_label = new QLabel(horizontalLayoutWidget_2);
        file_backup_label->setObjectName("file_backup_label");
        file_backup_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(file_backup_label);

        file_backup_lineEdit = new QLineEdit(horizontalLayoutWidget_2);
        file_backup_lineEdit->setObjectName("file_backup_lineEdit");

        horizontalLayout_2->addWidget(file_backup_lineEdit);

        file_backup_Btn = new QPushButton(horizontalLayoutWidget_2);
        file_backup_Btn->setObjectName("file_backup_Btn");

        horizontalLayout_2->addWidget(file_backup_Btn);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 5);
        stackedWidget->addWidget(file_backup);
        online_doc = new QWidget();
        online_doc->setObjectName("online_doc");
        online_doc_label1 = new QLabel(online_doc);
        online_doc_label1->setObjectName("online_doc_label1");
        online_doc_label1->setGeometry(QRect(10, 10, 101, 61));
        online_doc_comboBox = new QComboBox(online_doc);
        online_doc_comboBox->addItem(QString());
        online_doc_comboBox->addItem(QString());
        online_doc_comboBox->addItem(QString());
        online_doc_comboBox->setObjectName("online_doc_comboBox");
        online_doc_comboBox->setGeometry(QRect(110, 30, 111, 22));
        online_doc_timeEdit_1 = new QTimeEdit(online_doc);
        online_doc_timeEdit_1->setObjectName("online_doc_timeEdit_1");
        online_doc_timeEdit_1->setGeometry(QRect(110, 80, 118, 22));
        online_doc_label2 = new QLabel(online_doc);
        online_doc_label2->setObjectName("online_doc_label2");
        online_doc_label2->setGeometry(QRect(10, 60, 101, 61));
        online_doc_timeEdit_2 = new QTimeEdit(online_doc);
        online_doc_timeEdit_2->setObjectName("online_doc_timeEdit_2");
        online_doc_timeEdit_2->setGeometry(QRect(110, 150, 118, 22));
        online_doc_label2_2 = new QLabel(online_doc);
        online_doc_label2_2->setObjectName("online_doc_label2_2");
        online_doc_label2_2->setGeometry(QRect(10, 140, 81, 41));
        label = new QLabel(online_doc);
        label->setObjectName("label");
        label->setGeometry(QRect(110, 120, 111, 20));
        stackedWidget->addWidget(online_doc);
        QWidget::setTabOrder(treeWidget, all_setting_spinBox);
        QWidget::setTabOrder(all_setting_spinBox, all_setting_checkBox);
        QWidget::setTabOrder(all_setting_checkBox, file_system_lineEdit);
        QWidget::setTabOrder(file_system_lineEdit, file_system_Btn);
        QWidget::setTabOrder(file_system_Btn, file_see_spinBox);
        QWidget::setTabOrder(file_see_spinBox, email_service_lineEdit_1);
        QWidget::setTabOrder(email_service_lineEdit_1, email_service_lineEdit_2);
        QWidget::setTabOrder(email_service_lineEdit_2, email_service_lineEdit_3);
        QWidget::setTabOrder(email_service_lineEdit_3, email_service_lineEdit_4);
        QWidget::setTabOrder(email_service_lineEdit_4, email_service_lineEdit_5);
        QWidget::setTabOrder(email_service_lineEdit_5, email_service_lineEdit_6);
        QWidget::setTabOrder(email_service_lineEdit_6, file_backup_lineEdit);
        QWidget::setTabOrder(file_backup_lineEdit, file_backup_Btn);
        QWidget::setTabOrder(file_backup_Btn, online_doc_comboBox);
        QWidget::setTabOrder(online_doc_comboBox, online_doc_timeEdit_1);

        retranslateUi(Setting);

        stackedWidget->setCurrentIndex(5);


        QMetaObject::connectSlotsByName(Setting);
    } // setupUi

    void retranslateUi(QWidget *Setting)
    {
        Setting->setWindowTitle(QCoreApplication::translate("Setting", "\350\256\276\347\275\256", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("Setting", "\350\256\276\347\275\256", nullptr));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("Setting", "\346\200\273\344\275\223\350\256\276\347\275\256", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem2->setText(0, QCoreApplication::translate("Setting", "\346\226\207\344\273\266\347\263\273\347\273\237", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem2->child(0);
        ___qtreewidgetitem3->setText(0, QCoreApplication::translate("Setting", "\351\273\230\350\256\244\344\275\277\347\224\250\347\233\256\345\275\225", nullptr));
        QTreeWidgetItem *___qtreewidgetitem4 = treeWidget->topLevelItem(2);
        ___qtreewidgetitem4->setText(0, QCoreApplication::translate("Setting", "\346\226\207\344\273\266\346\237\245\347\234\213", nullptr));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem4->child(0);
        ___qtreewidgetitem5->setText(0, QCoreApplication::translate("Setting", "\345\255\227\344\275\223\345\244\247\345\260\217", nullptr));
        QTreeWidgetItem *___qtreewidgetitem6 = treeWidget->topLevelItem(3);
        ___qtreewidgetitem6->setText(0, QCoreApplication::translate("Setting", "\351\202\256\344\273\266\346\234\215\345\212\241", nullptr));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem6->child(0);
        ___qtreewidgetitem7->setText(0, QCoreApplication::translate("Setting", "\346\224\266\345\217\221\344\272\272", nullptr));
        QTreeWidgetItem *___qtreewidgetitem8 = ___qtreewidgetitem6->child(1);
        ___qtreewidgetitem8->setText(0, QCoreApplication::translate("Setting", "\350\256\276\347\275\256", nullptr));
        QTreeWidgetItem *___qtreewidgetitem9 = treeWidget->topLevelItem(4);
        ___qtreewidgetitem9->setText(0, QCoreApplication::translate("Setting", "\346\226\207\344\273\266\345\244\207\344\273\275", nullptr));
        QTreeWidgetItem *___qtreewidgetitem10 = ___qtreewidgetitem9->child(0);
        ___qtreewidgetitem10->setText(0, QCoreApplication::translate("Setting", "\345\244\207\344\273\275\350\267\257\345\276\204", nullptr));
        QTreeWidgetItem *___qtreewidgetitem11 = treeWidget->topLevelItem(5);
        ___qtreewidgetitem11->setText(0, QCoreApplication::translate("Setting", "\345\244\207\345\277\230\346\227\245\347\250\213", nullptr));
        QTreeWidgetItem *___qtreewidgetitem12 = ___qtreewidgetitem11->child(0);
        ___qtreewidgetitem12->setText(0, QCoreApplication::translate("Setting", "\345\210\260\346\234\237\346\217\220\351\206\222\346\226\271\345\274\217", nullptr));
        QTreeWidgetItem *___qtreewidgetitem13 = ___qtreewidgetitem11->child(1);
        ___qtreewidgetitem13->setText(0, QCoreApplication::translate("Setting", "\346\217\220\345\211\215\345\244\232\344\271\205\346\217\220\351\206\222", nullptr));
        treeWidget->setSortingEnabled(__sortingEnabled);

        all_setting_checkBox->setText(QCoreApplication::translate("Setting", "\346\230\257\345\220\246\345\220\257\347\224\250", nullptr));
        all_setting_label2->setText(QCoreApplication::translate("Setting", "\346\211\230\347\233\230", nullptr));
        all_setting_label1->setText(QCoreApplication::translate("Setting", "\345\205\250\345\261\200\345\255\227\344\275\223\345\244\247\345\260\217", nullptr));
        file_system_label->setText(QCoreApplication::translate("Setting", "\351\273\230\350\256\244\n"
"\345\220\257\347\224\250\n"
"\347\233\256\345\275\225", nullptr));
        file_system_Btn->setText(QCoreApplication::translate("Setting", "\351\200\211\345\217\226\n"
"\350\267\257\345\276\204", nullptr));
        file_see_label->setText(QCoreApplication::translate("Setting", "\345\255\227\344\275\223\345\244\247\345\260\217", nullptr));
        email_service_label_4->setText(QCoreApplication::translate("Setting", "\347\253\257\345\217\243", nullptr));
        email_service_label_2->setText(QCoreApplication::translate("Setting", "\347\224\250\346\210\267\345\220\215", nullptr));
        email_service_label_3->setText(QCoreApplication::translate("Setting", "\345\257\206\347\240\201", nullptr));
        email_service_label_1->setText(QCoreApplication::translate("Setting", "\346\234\215\345\212\241\345\231\250", nullptr));
        email_service_label_5->setText(QCoreApplication::translate("Setting", "\345\217\221\344\273\266\344\272\272", nullptr));
        email_service_label_6->setText(QCoreApplication::translate("Setting", "\346\224\266\344\273\266\344\272\272", nullptr));
        file_backup_label->setText(QCoreApplication::translate("Setting", "\347\250\213\345\272\217\n"
"\345\244\207\344\273\275\n"
"\347\233\256\345\275\225", nullptr));
        file_backup_Btn->setText(QCoreApplication::translate("Setting", "\351\200\211\345\217\226\n"
"\350\267\257\345\276\204", nullptr));
        online_doc_label1->setText(QCoreApplication::translate("Setting", "\346\217\220\351\206\222\346\226\271\345\274\217", nullptr));
        online_doc_comboBox->setItemText(0, QCoreApplication::translate("Setting", "\344\270\215\346\217\220\351\206\222", nullptr));
        online_doc_comboBox->setItemText(1, QCoreApplication::translate("Setting", "\345\274\271\347\252\227\346\217\220\351\206\222", nullptr));
        online_doc_comboBox->setItemText(2, QCoreApplication::translate("Setting", "\351\202\256\344\273\266\346\217\220\351\206\222", nullptr));

        online_doc_label2->setText(QCoreApplication::translate("Setting", "\346\217\220\345\211\215\345\244\232\344\271\205\346\217\220\351\206\222", nullptr));
        online_doc_label2_2->setText(QCoreApplication::translate("Setting", "\346\257\217\346\254\241\346\217\220\351\206\222\351\227\264\351\232\224\346\227\266\351\227\264", nullptr));
        label->setText(QCoreApplication::translate("Setting", "\345\215\225\344\275\215\357\274\210\346\227\266:\345\210\206\357\274\211", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Setting: public Ui_Setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
