#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    createNewTab([]() { return new TableTab(); }, "New Table Tab");
}

void MainWindow::on_actionopen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);;All Files (*)"));
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
    int currentIndex = ui->tabWidget->currentIndex();
    if (currentIndex < 0) {
        QMessageBox::warning(this, tr("Error"), tr("No tab to save"));
        return;
    }

    TabAbstract* currentTab = qobject_cast<TabAbstract*>(ui->tabWidget->widget(currentIndex));
    if (!currentTab) {
        QMessageBox::warning(this, tr("Error"), tr("Current tab is not valid"));
        return;
    }

    QString fileFilter;
    if (dynamic_cast<TextTab*>(currentTab)) {
        fileFilter = tr("Text Files (*.txt);;All Files (*)");
    } else if (dynamic_cast<TableTab*>(currentTab)) {
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
        return new TableTab();
    } else {
        return nullptr;
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    qDebug() << "Current tab index: " << index;
}

void MainWindow::on_actionclose_triggered()
{
    int currentIndex = ui->tabWidget->currentIndex();
    if (currentIndex >= 0) {
        ui->tabWidget->removeTab(currentIndex);
    } else {
        qDebug() << "No tab to close.";
    }
}

void MainWindow::on_actiondownload_triggered()
{
    int currentIndex = ui->tabWidget->currentIndex();
    TabAbstract* currentTab = qobject_cast<TabAbstract*>(ui->tabWidget->widget(currentIndex));
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
    int currentIndex = ui->tabWidget->currentIndex();
    TableTab* currentTab = dynamic_cast<TableTab*>(ui->tabWidget->widget(currentIndex));
    if (currentTab) {
        currentTab->addRow();
    } else {
        QMessageBox::warning(this, tr("Error"), tr("Current tab is not a table."));
    }
}

void MainWindow::on_actionsub_triggered()
{
    int currentIndex = ui->tabWidget->currentIndex();
    TableTab* currentTab = dynamic_cast<TableTab*>(ui->tabWidget->widget(currentIndex));
    if (currentTab) {
        currentTab->addColumn();
    } else {
        QMessageBox::warning(this, tr("Error"), tr("Current tab is not a table."));
    }
}

void MainWindow::on_actionlink_server_triggered()
{
    int currentIndex = ui->tabWidget->currentIndex();
    TableTab* currentTab = qobject_cast<TableTab*>(ui->tabWidget->widget(currentIndex));
    if (currentTab) {
        currentTab->setLinkStatus(true);
        Epoll* epoll = new Epoll(nullptr, currentTab);
        epoll->show();
    } else {
        qDebug() << "Failed to cast current tab to TabAbstract*";
    }
}
