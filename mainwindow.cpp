#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DLfromNet.h"
#include "TabHandleTXT.h"
#include "TabHandleCSV.h"
#include "QDockWidget"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("My Application");
    setWindowIcon(QIcon(":/images.jpg"));

    m_csvLinkServer = new csvLinkServer(this);
    m_csvLinkServer->show();
//    ui->dockRight->setWidget(m_csvLinkServer);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actiontxt_file_triggered()
{
    createNewTab([]() { return new TextTab(); }, "New Text Tab");
}

void MainWindow::on_actionscv_file_triggered()
{
    createNewTab([]() { return new TabHandleCSV(); }, "New Table Tab");
}

void MainWindow::on_actionopen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                    tr("CSV Files (*.csv);;Text Files (*.txt);;All Files (*)"));
    if (fileName.isEmpty())
        return;

    TabAbstract* newTab = createTabByFileName(fileName);
    if (newTab) {
        newTab->loadFromFile(fileName);
        QFileInfo fileInfo(fileName);
        QString baseName = fileInfo.fileName();
        ui->tabWidget->addTab(newTab, baseName);
    } else {
        QMessageBox::warning(this, tr("Error"), tr("Unsupported file type"));
    }
}

void MainWindow::on_actionsave_triggered()
{
    auto currentTab = getCurrentTab<TabAbstract>();
    if (!currentTab) return;

    QString fileFilter;
    if (dynamic_cast<TextTab*>(currentTab)) {
        fileFilter = tr("Text Files (*.txt);;All Files (*)");
    } else if (dynamic_cast<TabHandleCSV*>(currentTab)) {
        fileFilter = tr("CSV Files (*.csv);;All Files (*)");
    } else {
        fileFilter = tr("All Files (*)");
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", fileFilter);
    if (fileName.isEmpty())
        return;

    currentTab->saveToFile(fileName);
}

void MainWindow::createNewTab(std::function<TabAbstract*()> tabFactory, const QString &tabName)
{
    TabAbstract* newTab = tabFactory();
    ui->tabWidget->addTab(newTab, tabName);
}

TabAbstract* MainWindow::createTabByFileName(const QString &fileName)
{
    if (fileName.endsWith(".txt", Qt::CaseInsensitive)) {
        return new TextTab();
    } else if (fileName.endsWith(".csv", Qt::CaseInsensitive)) {
        return new TabHandleCSV();
    } else {
        return nullptr;
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    currentIndex = index;
    qDebug() << "Current tab index: " << index;
}

void MainWindow::on_actionclose_triggered()
{
    if (currentIndex >= 0) {
        ui->tabWidget->removeTab(currentIndex);
    } else {
        qDebug() << "No tab to close.";
    }
}

void MainWindow::on_actiondownload_triggered()
{
    auto currentTab = getCurrentTab<TabAbstract>();
    if (currentTab) {
        downLoad* downloadWidget = new downLoad();
        connect(downloadWidget, &downLoad::fileDownloaded, this, &MainWindow::handleFileDownload);
        downloadWidget->show();
    } else {
        qDebug() << "Failed to cast current tab to TabAbstract*";
    }
}

void MainWindow::handleFileDownload(const QString &fileName, const QByteArray &fileContent)
{
    TabAbstract* newTab = createTabByFileName(fileName);
    if (newTab) {
        newTab->loadFromContent(fileContent);
        ui->tabWidget->addTab(newTab, fileName);
    } else {
        QMessageBox::warning(this, tr("Error"), tr("Unsupported file type"));
    }
}

void MainWindow::on_actionadd_triggered()
{
    handleTableTabAction(&TabHandleCSV::addRow, tr("Current tab is not a table."));
}

void MainWindow::on_actionsub_triggered()
{
    handleTableTabAction(&TabHandleCSV::addColumn, tr("Current tab is not a table."));
}

void MainWindow::on_actionlink_server_triggered()
{
    auto currentTab = getCurrentTab<TabHandleCSV>();
    if (currentTab) {
        currentTab->setLinkStatus(true);
        csvLinkServer* m_csvLinkServer = new csvLinkServer(nullptr, currentTab);
        m_csvLinkServer->show();
    } else {
        qDebug() << "Failed to cast current tab to TabAbstract*";
    }
}

void MainWindow::on_actiondel_row_triggered()
{
    handleTableTabAction(&TabHandleCSV::deleteRow, tr("Current tab is not a table."));
}

void MainWindow::on_actiondel_col_triggered()
{
    handleTableTabAction(&TabHandleCSV::deleteColumn, tr("Current tab is not a table."));
}

template<typename T>
T* MainWindow::getCurrentTab()
{
    QWidget* currentWidget = ui->tabWidget->widget(currentIndex);
    T* currentTab = qobject_cast<T*>(currentWidget);
    if (!currentTab) {
        QMessageBox::warning(this, tr("Error"), tr("Current tab is not valid"));
    }
    return currentTab;
}

template<typename Func>
void MainWindow::handleTableTabAction(Func func, const QString &errorMessage)
{
    auto currentTab = getCurrentTab<TabHandleCSV>();
    if (currentTab) {
        (currentTab->*func)();
    } else {
        QMessageBox::warning(this, tr("Error"), errorMessage);
    }
}
