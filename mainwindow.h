#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <functional>
#include "TabAbstract.h"
#include "csvLinkServer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    void on_actionlink_server_triggered();
    void on_actiondel_row_triggered();
    void on_actiondel_col_triggered();

private:
    Ui::MainWindow *ui;
    int currentIndex;

    csvLinkServer* m_csvLinkServer;
    void createNewTab(std::function<TabAbstract*()> tabFactory, const QString &tabName);
    TabAbstract* createTabByFileName(const QString &fileName);

    template<typename T>
    T* getCurrentTab();

    template<typename Func>
    void handleTableTabAction(Func func, const QString &errorMessage);
};

#endif // MAINWINDOW_H
