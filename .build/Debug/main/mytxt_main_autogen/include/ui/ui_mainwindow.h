/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionopen;
    QAction *actionsave;
    QAction *actionadd;
    QAction *actionsub;
    QAction *actionclose;
    QAction *actiondownload;
    QAction *actiontxt_file;
    QAction *actionscv_file;
    QAction *actiondel_row;
    QAction *actiondel_col;
    QAction *actionshe;
    QWidget *centralwidget;
    QWidget *combinedWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QStackedWidget *stackedWidget;
    QMenuBar *menubar;
    QMenu *menufile;
    QMenu *menunew;
    QMenu *recentFile;
    QMenu *menuaction;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/usedimage/package.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        actionopen = new QAction(MainWindow);
        actionopen->setObjectName("actionopen");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/database_go.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionopen->setIcon(icon1);
        actionsave = new QAction(MainWindow);
        actionsave->setObjectName("actionsave");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/table_save.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionsave->setIcon(icon2);
        actionadd = new QAction(MainWindow);
        actionadd->setObjectName("actionadd");
        actionsub = new QAction(MainWindow);
        actionsub->setObjectName("actionsub");
        actionclose = new QAction(MainWindow);
        actionclose->setObjectName("actionclose");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/image/cross.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionclose->setIcon(icon3);
        actiondownload = new QAction(MainWindow);
        actiondownload->setObjectName("actiondownload");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/image/arrow_refresh_small.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actiondownload->setIcon(icon4);
        actiontxt_file = new QAction(MainWindow);
        actiontxt_file->setObjectName("actiontxt_file");
        actionscv_file = new QAction(MainWindow);
        actionscv_file->setObjectName("actionscv_file");
        actiondel_row = new QAction(MainWindow);
        actiondel_row->setObjectName("actiondel_row");
        actiondel_col = new QAction(MainWindow);
        actiondel_col->setObjectName("actiondel_col");
        actionshe = new QAction(MainWindow);
        actionshe->setObjectName("actionshe");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/png/Settings.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionshe->setIcon(icon5);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        combinedWidget = new QWidget(centralwidget);
        combinedWidget->setObjectName("combinedWidget");
        combinedWidget->setGeometry(QRect(50, 20, 271, 441));
        gridLayout_2 = new QGridLayout(combinedWidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(combinedWidget);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(combinedWidget);
        stackedWidget->setObjectName("stackedWidget");

        gridLayout->addWidget(stackedWidget, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 16));
        menufile = new QMenu(menubar);
        menufile->setObjectName("menufile");
        menunew = new QMenu(menufile);
        menunew->setObjectName("menunew");
        recentFile = new QMenu(menufile);
        recentFile->setObjectName("recentFile");
        menuaction = new QMenu(menubar);
        menuaction->setObjectName("menuaction");
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menufile->menuAction());
        menubar->addAction(menuaction->menuAction());
        menubar->addAction(menu->menuAction());
        menufile->addAction(menunew->menuAction());
        menufile->addAction(recentFile->menuAction());
        menufile->addAction(actionopen);
        menufile->addAction(actionsave);
        menufile->addAction(actionclose);
        menufile->addAction(actiondownload);
        menunew->addAction(actiontxt_file);
        menunew->addAction(actionscv_file);
        menuaction->addAction(actionadd);
        menuaction->addAction(actiondel_row);
        menuaction->addAction(actionsub);
        menuaction->addAction(actiondel_col);
        menu->addAction(actionshe);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "SmartDesk", nullptr));
        actionopen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
#if QT_CONFIG(shortcut)
        actionopen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionsave->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
#if QT_CONFIG(shortcut)
        actionsave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionadd->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\350\241\214", nullptr));
        actionsub->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\345\210\227", nullptr));
        actionclose->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
#if QT_CONFIG(shortcut)
        actionclose->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+W", nullptr));
#endif // QT_CONFIG(shortcut)
        actiondownload->setText(QCoreApplication::translate("MainWindow", "\344\270\213\350\275\275", nullptr));
#if QT_CONFIG(shortcut)
        actiondownload->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+D", nullptr));
#endif // QT_CONFIG(shortcut)
        actiontxt_file->setText(QCoreApplication::translate("MainWindow", "txt\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(shortcut)
        actiontxt_file->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N, Ctrl+T", nullptr));
#endif // QT_CONFIG(shortcut)
        actionscv_file->setText(QCoreApplication::translate("MainWindow", "scv\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(shortcut)
        actionscv_file->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N, Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actiondel_row->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\350\241\214", nullptr));
        actiondel_col->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\345\210\227", nullptr));
        actionshe->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\347\225\214\351\235\242", nullptr));
        menufile->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menunew->setTitle(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
        recentFile->setTitle(QCoreApplication::translate("MainWindow", "\350\256\260\345\275\225", nullptr));
        menuaction->setTitle(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\345\267\245\345\205\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
