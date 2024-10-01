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

#include "TabAbstract.h"
#include "RecentFilesManager.h"
#include "TabHandleTXT.h"
#include "TabHandleCSV.h"
#include "WidgetFunctional.h"

#include "../onlinedoc/WOnlineDoc.h"
#include "../setting/Setting.h"
#include "../schedule/WSchedule.h"
#include "../filetag/WFileTag.h"
#include "../filehis/WFileHis.h"

#include "../manager/DBSQlite.h"
#include "../manager/DBMySQL.h"
#include "../email/sendemail.h"

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

private slots:
    void on_actionopen_triggered();
    void on_actionsave_triggered();
    void on_actionclose_triggered();
    void on_actiondownload_triggered();
    void handleFileDownload(const QString &fileName, const QByteArray &fileContent);
    void on_actionscv_file_triggered();
    void on_actiontxt_file_triggered();
    void on_actionadd_triggered();
    void on_actionsub_triggered();
    void on_actiondel_row_triggered();
    void on_actiondel_col_triggered();

    void handleFilePathSent();
    void openFile(const QString &filePath);
    void on_actionshe_triggered();
    void showUserInfoDialog();
    void receiveSendEmailForm(SendEmail *form);


private:

    int currentIndex = 0;
    QTabWidget *tabWidget;
    Ui::MainWindow *ui;
    RecentFilesManager *recentFilesManager;
    QWidget * widgetr;

    DBSQlite *dbSqlite;
    DBMySQL *dbMysql;

    WFileTag * wfiletag;
    WFileHis * wfilehis;

    WOnlineDoc* wonlinedoc;
    WidgetFunctional* widgetfunc;
    Setting * setiing;
    WSchedule * schedule;

    void initFunc();
    void initSpli();


    void createNewTab(std::function<TabAbstract*()> tabFactory, const QString &tabName);
    TabAbstract* createTabByFileName(const QString &fileName);

    template<typename T>
    T* getCurrentTab();

    template<typename Func>
    void handleTableTabAction(Func func, const QString &errorMessage);
};

#endif // MAINWINDOW_H
