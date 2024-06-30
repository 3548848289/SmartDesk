#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "texttab.h"
#include "tabletab.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializeTabs(2, []() { return new TextTab(); });
    initializeTabs(2, []() { return new TableTab(); });
}

void MainWindow::initializeTabs(int numberOfTabs, std::function<AbstractTab*()> tabFactory)
{
    for (int i = 0; i < numberOfTabs; i++) {
        AbstractTab* newTab = tabFactory();
        tab_pool.push_back(newTab);
        freeTabs.push(i);
    }
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

    if (!freeTabs.isEmpty()) {
        int tabIndex = freeTabs.pop();

        if (tabIndex >= 0 && tabIndex < tab_pool.size()) {
            AbstractTab* tab = tab_pool[tabIndex];
            tab->loadFromFile(fileName);

            QFileInfo fileInfo(fileName);
            QString baseName = fileInfo.fileName();
            ui->tabWidget->addTab(tab, baseName);
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Invalid tab index"));
        }
    } else {
        QMessageBox::warning(this, tr("No More Tabs"), tr("No more tabs available in the pool."));
    }
}


void MainWindow::on_actionsave_triggered()
{
    int currentIndex = ui->tabWidget->currentIndex();
    if (currentIndex < 0 || currentIndex >= tab_pool.size()) {
        QMessageBox::warning(this, tr("Error"), tr("No tab to save"));
        return;
    }

    AbstractTab* currentTab = qobject_cast<AbstractTab*>(ui->tabWidget->widget(currentIndex));
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


void MainWindow::createNewTab(std::function<AbstractTab*()> tabFactory, const QString &tabName)
{
    if (!freeTabs.isEmpty()) {
        int tabIndex = freeTabs.pop();
        if (tabIndex >= 0 && tabIndex < tab_pool.size()) {
            AbstractTab* tab = tabFactory();
            tab_pool[tabIndex] = tab;
            tab->setText(tabName + " Content");
            ui->tabWidget->addTab(tab, tabName);
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Invalid tab index"));
        }
    } else {
        QMessageBox::warning(this, tr("No More Tabs"), tr("No more tabs available in the pool."));
    }
}



void MainWindow::on_tabWidget_currentChanged(int index)
{
    qDebug() << "Current tab index: " << index;
}

void MainWindow::on_actionclose_triggered()
{
    int currentIndex = ui->tabWidget->currentIndex();

    if (currentIndex >= 0 && currentIndex < tab_pool.size()) {
        ui->tabWidget->removeTab(currentIndex);
        freeTabs.push(currentIndex);
    } else {
        qDebug() << "No tab to close.";
    }
}

void MainWindow::on_actiondownload_triggered()
{
    int currentIndex = ui->tabWidget->currentIndex();
    AbstractTab* currentTab = qobject_cast<AbstractTab*>(ui->tabWidget->widget(currentIndex));
    if (currentTab) {
        Http* http = new Http();
        connect(http, &Http::fileDownloaded, this, &MainWindow::handleFileDownload);
        http->show();
    } else {
        qDebug() << "Failed to cast current tab to AbstractTab*";
    }
}

void MainWindow::handleFileDownload(const QString &fileName, const QByteArray &fileContent)
{
    if (!freeTabs.isEmpty()) {
        int tabIndex = freeTabs.pop();

        if (tabIndex >= 0 && tabIndex < tab_pool.size()) {
            AbstractTab* tab = tab_pool[tabIndex];
            tab->loadFromContent(fileContent);
            ui->tabWidget->addTab(tab, fileName);
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Invalid tab index"));
        }
    } else {
        QMessageBox::warning(this, tr("No More Tabs"), tr("No more tabs available in the pool."));
    }
}


MainWindow::~MainWindow()
{
    delete ui;
    qDeleteAll(tab_pool);
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
    AbstractTab* currentTab = qobject_cast<AbstractTab*>(ui->tabWidget->widget(currentIndex));
    if (currentTab) {
        Epoll* epoll = new Epoll();
        epoll->show();
    } else {
        qDebug() << "Failed to cast current tab to AbstractTab*";
    }
}

