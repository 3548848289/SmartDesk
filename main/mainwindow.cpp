#include "./include/mainwindow.h"
#include "ui/ui_mainwindow.h"


void MainWindow::initFunc()
{

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
    controlFrame = new ControlFrame(this);

    ui->stackedWidget->setObjectName("pWidget");
    ui->stackedWidget->setStyleSheet("QWidget#pWidget { border: 1px solid rgb(28, 251, 255); }");
    ui->stackedWidget->addWidget(widgetr);
    ui->stackedWidget->addWidget(wonlinedoc);
    ui->stackedWidget->addWidget(schedule);
    ui->stackedWidget->addWidget(controlFrame);
    ui->stackedWidget->setCurrentWidget(widgetr);

    connect(widgetfunc, &WidgetFunctional::showFiletag, this, [=] {
        ui->stackedWidget->setCurrentWidget(widgetr); });

    connect(widgetfunc, &WidgetFunctional::showwOnlinedoc, this, [=] {
        ui->stackedWidget->setCurrentWidget(wonlinedoc); });

    connect(widgetfunc, &WidgetFunctional::showWSchedule, this, [=] {
        ui->stackedWidget->setCurrentWidget(schedule); });
    connect(widgetfunc, &WidgetFunctional::sendEmailForm, this, &MainWindow::receiveSendEmailForm);

    connect(widgetfunc, &WidgetFunctional::showDraw, this, [=] {
        ui->stackedWidget->setCurrentWidget(controlFrame);
        QWidget *currentWidget = tabWidget->currentWidget();
        TabHandleIMG *tabHandleImg = qobject_cast<TabHandleIMG*>(currentWidget);
        if (tabHandleImg) {
            tabHandleImg->showControlFrame(controlFrame);
        } else {
            qWarning() << "Current widget is not a TabHandleIMG instance!";
        }
    });

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

void MainWindow::initSmal()
{
    loginButton = new QPushButton(this);
    loginButton->setFixedSize(30, 30);
    loginButton->setStyleSheet("border: none; border-radius: 15px;");
    loginButton->setIcon(QIcon(":/image/login.png"));
    loginButton->setIconSize(loginButton->size());

    ui->menubar->setCornerWidget(loginButton, Qt::TopRightCorner);
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::showUserInfoDialog);


    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    connect(tabWidget, &QTabWidget::tabCloseRequested, this, [this](int index) {
        on_actionclose_triggered();
    });
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow),
    recentFilesManager(new RecentFilesManager(this)),
    dbSqlite(&DBSQlite::instance())
    , dbMysql(&DBMySQL::instance())
{
    dbSqlite->open();
    ui->setupUi(this);

    initSmal();
    initFunc();
    initSpli();

    connect(tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);

    connect(wonlinedoc->m_csvLinkServer, &csvLinkServer::filePathSent, this, &MainWindow::handleFilePathSent);
    connect(recentFilesManager, &RecentFilesManager::fileOpened, this, &MainWindow::openFile);
    connect(wfiletag, &WFileTag::fileOpened, this, &MainWindow::openFile);
    connect(schedule, &WSchedule::fileClicked, this, &MainWindow::openFile);

    recentFilesManager->populateRecentFilesMenu(ui->recentFile);
}

void MainWindow::onTabChanged(int index) {
    qDebug() << "MainWindow::MainWindow" << index;
    currentIndex = index;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showUserInfoDialog() {
    DInfo *dinfo = widgetfunc->getDInfo();
    if (dinfo) {
        QPixmap avatar = dinfo->getStoredAvatar();
        if (!avatar.isNull()) {
            loginButton->setIcon(QIcon(avatar.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
            loginButton->setIconSize(QSize(15, 15));
        }
        dinfo->exec();
    } else {
        QMessageBox::warning(this, "警告", "未登录");
    }
}

void MainWindow::receiveSendEmailForm(SendEmail *form)
{
    int newIndex = tabWidget->addTab(form, QLatin1String("Email"));
    form->show();
    tabWidget->setCurrentIndex(newIndex);
    ui->stackedWidget->setCurrentWidget(widgetr);
}

void MainWindow::on_actiontxt_file_triggered()
{
    createNewTab([]() { return new TextTab(""); }, "New Text Tab");
}

void MainWindow::on_actionscv_file_triggered()
{
    createNewTab([]() { return new TabHandleCSV(""); }, "New Table Tab");
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
        connect(newTab, &TabAbstract::contentModified, this, [this, newIndex, baseName]() {
            if (!tabWidget->tabText(newIndex).endsWith("*")) {
                tabWidget->setTabText(newIndex, baseName + "*");
            }
        });

        connect(newTab, &TabAbstract::contentSaved, this, [this, newIndex, baseName]() {
            qDebug() << baseName;
            tabWidget->setTabText(newIndex, QFileInfo(baseName).fileName());
        });
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

    // 获取当前的文件路径
    QString currentFilePath = currentTab->getCurrentFilePath();

    // 如果文件路径为空，说明这是第一次保存，弹出保存对话框
    if (currentFilePath.isEmpty()) {
        QString fileFilter;
        if (dynamic_cast<TextTab*>(currentTab))
            fileFilter = tr("Text Files (*.txt);;All Files (*)");
        else if (dynamic_cast<TabHandleCSV*>(currentTab))
            fileFilter = tr("CSV Files (*.csv);;All Files (*)");
        else
            fileFilter = tr("All Files (*)");

        currentFilePath = QFileDialog::getSaveFileName(this, tr("Save File"), "", fileFilter);
        if (currentFilePath.isEmpty())
            return;  // 如果用户取消保存
    }
    currentTab->save();
    currentTab->setCurrentFilePath(currentFilePath);
}


void MainWindow::createNewTab(std::function<TabAbstract*()> tabFactory, const QString &tabName)
{
    TabAbstract* newTab = tabFactory();
    int index = tabWidget->addTab(newTab, tabName);

    connect(newTab, &TabAbstract::contentModified, this, [this, index, tabName]() {
        if (!tabWidget->tabText(index).endsWith("*")) {
            tabWidget->setTabText(index, tabName + "*");
        }
    });

    connect(newTab, &TabAbstract::contentSaved, this, [this, index, tabName]() {
        tabWidget->setTabText(index, QFileInfo(tabName).fileName());
    });
}

TabAbstract* MainWindow::createTabByFileName(const QString &fileName)
{
    qDebug() << "MainWindow::createTabByFileName" << fileName;
    if (fileName.endsWith(".txt", Qt::CaseInsensitive) ||
        fileName.endsWith(".cpp", Qt::CaseInsensitive) ||
        fileName.endsWith(".qrc", Qt::CaseInsensitive) ||
        fileName.endsWith(".h", Qt::CaseInsensitive))
    {
        return new TextTab(fileName);  // 使用带路径的构造函数
    }
    else if (fileName.endsWith(".csv", Qt::CaseInsensitive))
    {
        return new TabHandleCSV(fileName);  // 使用带路径的构造函数
    }
    else if (fileName.endsWith(".png", Qt::CaseInsensitive) ||
             fileName.endsWith(".jpg", Qt::CaseInsensitive) ||
             fileName.endsWith(".jpeg", Qt::CaseInsensitive) ||
             fileName.endsWith(".bmp", Qt::CaseInsensitive))
    {
        return new TabHandleIMG(fileName);  // 使用带路径的构造函数
    }
    else
    {
        qDebug() << "Unsupported file type:" << fileName;
        return nullptr;
    }
}


void MainWindow::on_actionclose_triggered()
{
    int currentIndex = tabWidget->currentIndex();  // 获取当前选中的标签页索引
    if (currentIndex >= 0) {
        QWidget *widget = tabWidget->widget(currentIndex);

        if (!widget) {
            qDebug() << "No widget found at current index.";
            return;
        }

        TabAbstract *tab = qobject_cast<TabAbstract*>(widget);
        if (tab) {
            if (tab->confirmClose()) {
                tabWidget->removeTab(currentIndex);
            } else {
                qDebug() << "Tab close canceled by user.";
            }
        }
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


void MainWindow::handleFilePathSent()
{

    on_actionscv_file_triggered();
    auto currentTab = getCurrentTab<TabHandleCSV>();

    currentTab->setLinkStatus(true);
    wonlinedoc->m_csvLinkServer->bindTab(currentTab);
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



void MainWindow::on_actionadd_triggered()
{
    handleTableTabAction(&TabHandleCSV::addRow, tr("Current tab is not a table."));
}

void MainWindow::on_actionsub_triggered()
{
    handleTableTabAction(&TabHandleCSV::addColumn, tr("Current tab is not a table."));
}

void MainWindow::on_actiondel_row_triggered()
{
    handleTableTabAction(&TabHandleCSV::deleteRow, tr("Current tab is not a table."));
}

void MainWindow::on_actiondel_col_triggered()
{
    handleTableTabAction(&TabHandleCSV::deleteColumn, tr("Current tab is not a table."));
}

