#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::initializeTabs(int numberOfTabs)
{
    for (int i = 0; i < numberOfTabs; i++) {
        Tab* newTab = new Tab();
        tab_pool.push_back(newTab);
        freeTabs.push(i);
    }
}

void MainWindow::on_actionnew_triggered()
{
    if (!freeTabs.isEmpty())
    {
        int tabIndex = freeTabs.pop();
        if (tabIndex >= 0 && tabIndex < tab_pool.size()) {
            Tab* tab = tab_pool[tabIndex];
            ui->tabWidget->addTab(tab, "new Tab");
        }
        else
            qDebug() << "Invalid tabIndex: " << tabIndex;
    }
    else
        QMessageBox::warning(this, tr("No More Tabs"), tr("No more tabs available in the pool."));
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    currentIndex = index;
    qDebug() << "当前处于 tab 索引：" << index;
}

void MainWindow::on_actionclose_triggered()
{

    if (currentIndex >= 0 && currentIndex < tab_pool.size())
    {
        ui->tabWidget->removeTab(currentIndex);
        freeTabs.push(currentIndex);
    }
    else
        qDebug() << "No tab to close.";
}

void MainWindow::on_actionopen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Could not open file"));
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    if (!freeTabs.isEmpty())
    {
        int tabIndex = freeTabs.pop();
        if (tabIndex >= 0 && tabIndex < tab_pool.size())
        {
            Tab* tab = tab_pool[tabIndex];
            tab->TabSetText(content);

            QFileInfo fileInfo(fileName);
            QString baseName = fileInfo.fileName();
            ui->tabWidget->addTab(tab, baseName);
        }
        else
            qDebug() << "Invalid tabIndex: " << tabIndex;
    }
    else
        QMessageBox::warning(this, tr("No More Tabs"), tr("No more tabs available in the pool."));
}

void MainWindow::on_actionsave_triggered()
{

    if (currentIndex < 0 || currentIndex >= tab_pool.size()) {
        QMessageBox::warning(this, tr("Error"), tr("No tab to save"));
        return;
    }

    Tab* currentTab = qobject_cast<Tab*>(ui->tabWidget->widget(currentIndex));
    if (!currentTab)
    {
        QMessageBox::warning(this, tr("Error"), tr("Invalid tab"));
        return;
    }
    QString content = currentTab->TabGetText();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Could not save file"));
        return;
    }

    QTextStream out(&file);
    out << content;
    file.close();

    if (file.error() == QFile::NoError)
        QMessageBox::information(this, tr("Success"), tr("File saved successfully"));
    else
        QMessageBox::warning(this, tr("Error"), tr("File could not be saved"));
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Tab* firstTab = new Tab();
    firstTab->TabSetText("First Tab Content");
    ui->tabWidget->addTab(firstTab, "First Tab");
    initializeTabs(9);
}

MainWindow::~MainWindow()
{
    delete ui;
    qDeleteAll(tab_pool);
}

void MainWindow::on_actiondownload_triggered()
{
    Tab* currentTab = qobject_cast<Tab*>(ui->tabWidget->widget(currentIndex));
    if (currentTab) {
        Http* http = new Http();
        connect(http, &Http::fileDownloaded, this, &MainWindow::handleFileDownload);
        http->show();
    }
    else
        qDebug() << "Failed to cast current tab to Tab*";

}

void MainWindow::handleFileDownload(const QString &fileName, const QByteArray &fileContent)
{
    if (!freeTabs.isEmpty()) {
        int tabIndex = freeTabs.pop();
        if (tabIndex >= 0 && tabIndex < tab_pool.size()) {
            Tab* tab = tab_pool[tabIndex];
            tab->TabSetText(QString::fromUtf8(fileContent)); // Assuming fileContent is UTF-8 encoded
            ui->tabWidget->addTab(tab, fileName);
        }
        else
            QMessageBox::warning(this, tr("Error"), tr("Invalid tab index"));
    }
    else
        QMessageBox::warning(this, tr("No More Tabs"), tr("No more tabs available in the pool."));
}
