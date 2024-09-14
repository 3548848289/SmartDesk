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

#include "TabAbstract.h"
#include "WidgetRD.h"
#include "WidgetRU.h"
#include "TabHandleTXT.h"
#include "TabHandleCSV.h"
#include "RecentFilesManager.h"
#include "Setting.h"
#include "WidgetFunctional.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void showRU();
    void showRD();

private slots:
    void on_actionopen_triggered();
    void on_actionsave_triggered();
    void on_tabWidget_currentChanged(int index);
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

private:

    RecentFilesManager *recentFilesManager;
    Ui::MainWindow *ui;
    int currentIndex = 0;
    QTabWidget *tabWidget;
    QWidget * widgetr;

    WidgetRU * widgetru;
    WidgetRD* widgetrd;
    WidgetFunctional* widgetfunc;

    Setting * setiing;
    void createNewTab(std::function<TabAbstract*()> tabFactory, const QString &tabName);
    TabAbstract* createTabByFileName(const QString &fileName);

    template<typename T>
    T* getCurrentTab();

    template<typename Func>
    void handleTableTabAction(Func func, const QString &errorMessage);
};

#endif // MAINWINDOW_H
