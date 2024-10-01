#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"
#include <QSplitter>


void MainWindow::initFunc()
{
    if (!dbSqlite->open()) {
        QMessageBox::critical(this, "数据库错误", dbSqlite->lastError());
    }

    if (!dbMysql->open()) {
        QMessageBox::critical(this, "数据库错误", dbMysql->lastError());
    }
    
    widgetr = new QWidget(this);
    QGridLayout *gridLayout = new QGridLayout(widgetr);
    wfiletag = new WFileTag(dbSqlite, widgetr);
    wfilehis = new WFileHis(widgetr);
    QSplitter *splitter = new QSplitter(Qt::Vertical, widgetr);
    splitter->addWidget(wfiletag);
    splitter->addWidget(wfilehis);
    splitter->setSizes(QList<int>() << 500 << 200);
    gridLayout->addWidget(splitter, 0, 0);
    widgetr->setLayout(gridLayout);

    wonlinedoc = new WOnlineDoc(this);
    schedule = new WSchedule(dbSqlite, this);
    widgetfunc = new WidgetFunctional(dbMysql, this);
    ui->stackedWidget->setObjectName("pWidget");
    ui->stackedWidget->setStyleSheet("QWidget#pWidget { border: 1px solid rgb(28, 251, 255); }");
    ui->stackedWidget->addWidget(widgetr);
    ui->stackedWidget->addWidget(wonlinedoc);
    ui->stackedWidget->addWidget(schedule);
    ui->stackedWidget->setCurrentWidget(widgetr);

    connect(widgetfunc, &WidgetFunctional::showRU, this, [=] {
        ui->stackedWidget->setCurrentWidget(widgetr); });

    connect(widgetfunc, &WidgetFunctional::showRD, this, [=] {
        ui->stackedWidget->setCurrentWidget(wonlinedoc); });

    connect(widgetfunc, &WidgetFunctional::showWSchedule, this, [=] {
        ui->stackedWidget->setCurrentWidget(schedule); });

}

void MainWindow::initSpli()
{

    QSplitter *horizontalSplitter = new QSplitter(Qt::Horizontal);
    horizontalSplitter->addWidget(widgetfunc);
    horizontalSplitter->addWidget(tabWidget);
    horizontalSplitter->addWidget(ui->combinedWidget);

    horizontalSplitter->setStretchFactor(0, 0);
    horizontalSplitter->setStretchFactor(1, 1);
    horizontalSplitter->setStretchFactor(2, 2);

    setCentralWidget(horizontalSplitter);

    QList<int> sizes;
    sizes <<  60 << 500 << 240;
    horizontalSplitter->setSizes(sizes);
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow),
    recentFilesManager(new RecentFilesManager(this)),
    dbSqlite(&DBSQlite::instance()), dbMysql(&DBMySQL::instance())
{
    dbSqlite->open();
    ui->setupUi(this);
    setWindowTitle("QiHan在线文档");
    setWindowIcon(QIcon(":/usedimage/package.svg"));

    QPushButton *loginButton = new QPushButton("Login", ui->menubar);
    loginButton->setFixedSize(80, 30);
    ui->menubar->setCornerWidget(loginButton, Qt::TopRightCorner);
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::showUserInfoDialog);



    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    connect(tabWidget, &QTabWidget::tabCloseRequested, this, [this](int index) {
        tabWidget->removeTab(index);
    });

//    SendEmail *form = new SendEmail();  // 使用指针分配

//    form->setWindowTitle(QLatin1String("SimpleMailQt - Demo 2"));

//    form->show();

//    qDebug() << "邮件发送完成";

//    tabWidget->addTab(form, QLatin1String("邮件发送"));


    tabWidget->setStyleSheet(
        "QTabBar::tab {"
        "    background: #f0f0f0; color: #000000; padding: 5px;"
        "border: 1px solid #cccccc; border-bottom: none; }"
        "QTabBar::tab:selected {"
        "    background: #ffffff; color: #3598db; border-bottom: none; }"
        );
    initFunc();
    initSpli();

    connect(tabWidget, &QTabWidget::currentChanged, this, [this](int index) {currentIndex = index;});
    connect(wonlinedoc->m_csvLinkServer, &csvLinkServer::filePathSent, this, &MainWindow::handleFilePathSent);
    connect(recentFilesManager, &RecentFilesManager::fileOpened, this, &MainWindow::openFile);
    connect(wfiletag, &WFileTag::fileOpened, this, &MainWindow::openFile);
    connect(schedule, &WSchedule::fileClicked, this, &MainWindow::openFile);

    recentFilesManager->populateRecentFilesMenu(ui->recentFile);
}



MainWindow::~MainWindow()
{
    delete ui;
}

// 槽函数实现
void MainWindow::showUserInfoDialog() {
    DInfo *dinfo = widgetfunc->getDInfo();
    if (dinfo) {
        dinfo->exec();
    } else {
        QMessageBox::warning(this, "警告", "未登录");
    }
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
    } else
        QMessageBox::warning(this, tr("Error"), tr("Unsupported file type"));
}

void MainWindow::on_actionsave_triggered()
{
    auto currentTab = getCurrentTab<TabAbstract>();
    if (!currentTab) return;

    QString fileFilter;
    if (dynamic_cast<TextTab*>(currentTab))
        fileFilter = tr("Text Files (*.txt);;All Files (*)");
    else if (dynamic_cast<TabHandleCSV*>(currentTab))
        fileFilter = tr("CSV Files (*.csv);;All Files (*)");
    else
        fileFilter = tr("All Files (*)");

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
        fileName.endsWith(".h", Qt::CaseInsensitive))
        return new TextTab();
    else if (fileName.endsWith(".csv", Qt::CaseInsensitive))
        return new TabHandleCSV();
    else
        return nullptr;
}

void MainWindow::on_actionclose_triggered()
{
    if (currentIndex >= 0)
        tabWidget->removeTab(currentIndex);
    else
        qDebug() << "No tab to close.";
}

void MainWindow::on_actiondownload_triggered()
{
    auto currentTab = getCurrentTab<TabAbstract>();
    if (currentTab) {
        downLoad* downloadWidget = new downLoad();
        connect(downloadWidget, &downLoad::fileDownloaded, this, &MainWindow::handleFileDownload);
        downloadWidget->show();
    } else
        qDebug() << "Failed to cast current tab to TabAbstract*";
}

void MainWindow::handleFileDownload(const QString &fileName, const QByteArray &fileContent)
{
    TabAbstract* newTab = createTabByFileName(fileName);
    if (newTab) {
        newTab->loadFromContent(fileContent);
        tabWidget->addTab(newTab, fileName);
    } else
        QMessageBox::warning(this, tr("Error"), tr("Unsupported file type"));

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
    wonlinedoc->m_csvLinkServer->bindTab(currentTab);
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
