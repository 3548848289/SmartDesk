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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionopen;
    QAction *actionsave;
    QAction *actionclose;
    QAction *actiondownload;
    QAction *actiontxt_file;
    QAction *actionscv_file;
    QAction *actionshe;
    QAction *actiontest;
    QAction *actiondo;
    QAction *actionfind;
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QWidget *combinedWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QLabel *label;
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
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::DocumentOpen)) {
            icon1 = QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen);
        } else {
            icon1.addFile(QString::fromUtf8(":/image/database_go.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        actionopen->setIcon(icon1);
        actionsave = new QAction(MainWindow);
        actionsave->setObjectName("actionsave");
        QIcon icon2;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::DocumentSave)) {
            icon2 = QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave);
        } else {
            icon2.addFile(QString::fromUtf8(":/image/table_save.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        actionsave->setIcon(icon2);
        actionclose = new QAction(MainWindow);
        actionclose->setObjectName("actionclose");
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::EditClear));
        actionclose->setIcon(icon3);
        actiondownload = new QAction(MainWindow);
        actiondownload->setObjectName("actiondownload");
        QIcon icon4;
        QString iconThemeName = QString::fromUtf8("emblem-downloads");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QString::fromUtf8(":/image/arrow_refresh_small.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        actiondownload->setIcon(icon4);
        actiontxt_file = new QAction(MainWindow);
        actiontxt_file->setObjectName("actiontxt_file");
        QIcon icon5(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew));
        actiontxt_file->setIcon(icon5);
        actionscv_file = new QAction(MainWindow);
        actionscv_file->setObjectName("actionscv_file");
        actionscv_file->setIcon(icon5);
        actionshe = new QAction(MainWindow);
        actionshe->setObjectName("actionshe");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/png/Settings.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionshe->setIcon(icon6);
        actiontest = new QAction(MainWindow);
        actiontest->setObjectName("actiontest");
        QIcon icon7(QIcon::fromTheme(QIcon::ThemeIcon::UserAvailable));
        actiontest->setIcon(icon7);
        actiondo = new QAction(MainWindow);
        actiondo->setObjectName("actiondo");
        actionfind = new QAction(MainWindow);
        actionfind->setObjectName("actionfind");
        QIcon icon8(QIcon::fromTheme(QIcon::ThemeIcon::EditFind));
        actionfind->setIcon(icon8);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(310, 20, 221, 421));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        combinedWidget = new QWidget(verticalLayoutWidget);
        combinedWidget->setObjectName("combinedWidget");
        gridLayout_2 = new QGridLayout(combinedWidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(4);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, -1, -1, 0);
        stackedWidget = new QStackedWidget(combinedWidget);
        stackedWidget->setObjectName("stackedWidget");

        gridLayout->addWidget(stackedWidget, 1, 0, 1, 1);

        label = new QLabel(combinedWidget);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        verticalLayout->addWidget(combinedWidget);

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
        menuaction->addAction(actiondo);
        menu->addAction(actionshe);
        menu->addAction(actionfind);
        menu->addAction(actiontest);

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
        actionshe->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
#if QT_CONFIG(shortcut)
        actionshe->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+,", nullptr));
#endif // QT_CONFIG(shortcut)
        actiontest->setText(QCoreApplication::translate("MainWindow", "\346\265\213\350\257\225", nullptr));
        actiondo->setText(QCoreApplication::translate("MainWindow", "\346\223\215\347\272\265csv", nullptr));
        actionfind->setText(QCoreApplication::translate("MainWindow", "\346\237\245\346\211\276", nullptr));
#if QT_CONFIG(shortcut)
        actionfind->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+F", nullptr));
#endif // QT_CONFIG(shortcut)
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
