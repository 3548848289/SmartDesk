#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMainWindow>
#include <QMessageBox>
#include <QIcon>
#include <QFont>
#include "mainwindow.h"
#include "../../Setting/include/SettingManager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);

    int font_size = SettingManager::Instance().all_setting_fontsize();
    QFont font = QApplication::font();
    font.setPointSize(font_size);
    QApplication::setFont(font);

    MainWindow w;
    w.show();

    bool enableTray = SettingManager::Instance().all_setting_fenable_tray();

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
