#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMainWindow>
#include <QMessageBox>
#include <QIcon>
#include "mainwindow.h"
#include "../../setting/Setting.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);

    MainWindow w;
    w.show();
    // 从设置中读取托盘启用状态
    QSettings settings("MyCompany", "MyApp");
    bool enableTray = settings.value("enableTray", true).toBool();

    // enableTray = true;
    // if (enableTray) {
    //     qDebug() << "托盘启用";  // 调试信息，确保进入到这部分

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

    // }



    return app.exec();
}
