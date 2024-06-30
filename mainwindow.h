#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTableWidget>
#include <QStack>
#include "tab.h"
#include "http.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void initializeTabs(int numberOfTabs);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionopen_triggered();
    void on_actionsave_triggered();
    void on_actionnew_triggered();
    void on_tabWidget_currentChanged(int index);
    void on_actionclose_triggered();
    void on_actiondownload_triggered();
    void handleFileDownload(const QString &fileName, const QByteArray &fileContent);
private:
    Ui::MainWindow *ui;
    QStack<int> freeTabs;
    QList<Tab*> tab_pool;
    int currentIndex;
};
#endif // MAINWINDOW_H
