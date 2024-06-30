// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QFileDialog>
#include <QMessageBox>
#include "abstracttab.h"
#include "Http.h"

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

private:
    Ui::MainWindow *ui;
    QStack<int> freeTabs;
    QList<AbstractTab*> tab_pool;

    void createNewTab(std::function<AbstractTab*()> tabFactory, const QString &tabName);

    void initializeTabs(int numberOfTabs, std::function<AbstractTab*()> tabFactory);
};

#endif // MAINWINDOW_H
