#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <functional>
#include <QWidget>
#include <QDockWidget>
#include <QStackedWidget>
#include <QSplitter>

#include "TabAbstract.h"
#include "RecentFilesManager.h"
#include "TabHandleTXT.h"
#include "TabHandleCSV.h"
#include "../../ImageDispose/TabHandleIMG.h"
#include "WidgetFunctional.h"
#include "../../OnlineDoc/include/WOnlineDoc.h"
#include "../../Setting/Setting.h"
#include "../../TagSchedule/include/ScheduleWid.h"
#include "../../FileSystem/include/FileSystem.h"
#include "../../FileBackup/include/FileBackupList.h"
#include "../../manager/include/dbService.h"
#include "../../EmailService/SendEmail.h"
#include "../../ImageDispose/ControlFrame.h"
#include "ControlWidCSV.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void showUserInfo();

public slots:
    void onTabChanged(int index);

private slots:
    void on_actionopen_triggered();
    void on_actionsave_triggered();
    void on_actionclose_triggered();
    void on_actiondownload_triggered();
    void handleFileDownload(const QString &fileName, const QByteArray &fileContent);
    void on_actionscv_file_triggered();
    void on_actiontxt_file_triggered();

    void handleFilePathSent();
    void openFile(const QString &filePath);
    void on_actionshe_triggered();
    void showUserInfoDialog();
    void receiveSendEmailForm(SendEmail *form);

private:

    int currentIndex = 0;
    QPushButton *loginButton;
    QTabWidget *tabWidget;
    Ui::MainWindow *ui;
    RecentFilesManager *recentFilesManager;
    QWidget * widgetr;

    FileSystem * file_system;
    FileBackupList * file_backup_list;

    WOnlineDoc* wonlinedoc;
    WidgetFunctional* widgetfunc;
    Setting * setiing;
    ScheduleWid * schedule_wid;

    void initFunc();
    void initSpli();
    void initSmal();


    void createNewTab(std::function<TabAbstract*()> tabFactory, const QString &tabName);
    TabAbstract* createTabByFileName(const QString &fileName);

    template<typename T>
    T* getCurrentTab();

};

#endif // MAINWINDOW_H
