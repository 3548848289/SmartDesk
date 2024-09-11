#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow),
    recentFilesManager(new RecentFilesManager(this))
{

    ui->setupUi(this);
    setWindowTitle("QiHan在线文档");
    setWindowIcon(QIcon(":/image/package.svg"));

    ui->dockLeft->setWindowFlags(ui->dockLeft->windowFlags() | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    ui->dockLeft->setTitleBarWidget(ui->dockLWid);
    tabWidget = new QTabWidget(ui->dockLeft);
    connect(tabWidget, &QTabWidget::currentChanged, this, &MainWindow::on_tabWidget_currentChanged);

    ui->dockLeft->setWidget(tabWidget);

    widgetru = new WidgetRU(ui->dockRight);
    ui->verticalLayout->addWidget(widgetru);

    widgetrd = new WidgetRD(ui->dockRight);
    ui->verticalLayout->addWidget(widgetrd);
    connect(widgetrd->m_csvLinkServer, &csvLinkServer::filePathSent, this, &MainWindow::handleFilePathSent);

    splitDockWidget(ui->dockLeft, ui->dockRight, Qt::Horizontal);
    resizeDocks({ui->dockLeft, ui->dockRight}, {650, 350}, Qt::Horizontal);

    connect(recentFilesManager, &RecentFilesManager::fileOpened, this, &MainWindow::openFile);
    connect(widgetru, &WidgetRU::fileOpened, this, &MainWindow::openFile);

    recentFilesManager->populateRecentFilesMenu(ui->recentFile);

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
                                                    tr("All Files (*);;CSV Files (*.csv);;Text Files (*.txt)"));
    if (fileName.isEmpty())
        return;
    openFile(fileName);
}

void MainWindow::openFile(const QString &filePath)
{
    TabAbstract* newTab = createTabByFileName(filePath);
    if (newTab) {
        newTab->loadFromFile(filePath);
        QFileInfo fileInfo(filePath);
        QString baseName = fileInfo.fileName();

        int newIndex = tabWidget->addTab(newTab, baseName);
        tabWidget->setCurrentIndex(newIndex);

        recentFilesManager->addFile(filePath);
        recentFilesManager->populateRecentFilesMenu(ui->recentFile);

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
    tabWidget->addTab(newTab, tabName);
}

TabAbstract* MainWindow::createTabByFileName(const QString &fileName)
{
    if (fileName.endsWith(".txt", Qt::CaseInsensitive) ||
        fileName.endsWith(".cpp", Qt::CaseInsensitive) ||
        fileName.endsWith(".h", Qt::CaseInsensitive)) {
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
//    qDebug() << "Current tab index: " << index;
}

void MainWindow::on_actionclose_triggered()
{
    if (currentIndex >= 0) {
        tabWidget->removeTab(currentIndex);
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
        tabWidget->addTab(newTab, fileName);
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

void MainWindow::handleFilePathSent()
{

    on_actionscv_file_triggered();
    auto currentTab = getCurrentTab<TabHandleCSV>();

    currentTab->setLinkStatus(true);
    widgetrd->m_csvLinkServer->bindTab(currentTab);
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
    QWidget* currentWidget = tabWidget->widget(currentIndex);
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


void MainWindow::on_actionshe_triggered()
{
    setiing = new Setting();
    setiing->show();
}

