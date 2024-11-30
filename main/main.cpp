#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMainWindow>
#include <QMessageBox>
#include <QIcon>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    MainWindow w;
    w.show();
    QSystemTrayIcon trayIcon;
    trayIcon.setIcon(QIcon(":/usedimage/package.svg"));
    trayIcon.setToolTip("托盘程序示例");

    QMenu trayMenu;
    QAction showAction("显示主窗口", &trayMenu);
    QAction quitAction("退出", &trayMenu);

    trayMenu.addAction(&showAction);
    trayMenu.addSeparator();
    trayMenu.addAction(&quitAction);
    trayIcon.setContextMenu(&trayMenu);

    QObject::connect(&trayIcon, &QSystemTrayIcon::activated, [&w](QSystemTrayIcon::ActivationReason reason) {
        if (reason == QSystemTrayIcon::Trigger  ) {
            w.show(); w.raise(); w.activateWindow();
        }
    });

    QObject::connect(&showAction, &QAction::triggered, [&w]() {
        w.show(); w.raise(); w.activateWindow();
    });

    QObject::connect(&quitAction, &QAction::triggered, &app, &QApplication::quit);

    trayIcon.show();
    trayIcon.showMessage("托盘通知", "程序已最小化到托盘", QSystemTrayIcon::Information, 3000);

    return app.exec();
}
