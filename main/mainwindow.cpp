#include "include/mainwindow.h"
#include "ui/ui_mainwindow.h"
#include "../manager/include/dbService.h"


void MainWindow::initFunc()
{

    widgetr = new QWidget(this);
    QGridLayout *gridLayout = new QGridLayout(widgetr);
    file_system = new FileSystem(widgetr);
    file_backup_list = new FileBackupList(widgetr);
    QSplitter *splitter = new QSplitter(Qt::Vertical, widgetr);
    splitter->addWidget(file_system);
    splitter->addWidget(file_backup_list);
    splitter->setSizes(QList<int>() << 500 << 200);
    gridLayout->addWidget(splitter, 0, 0);
    widgetr->setLayout(gridLayout);

    wonlinedoc = new WOnlineDoc(this);
    schedule_wid= new ScheduleWid(this);
    widgetfunc = new WidgetFunctional(this);

    ui->stackedWidget->setObjectName("pWidget");
    ui->stackedWidget->setStyleSheet("QWidget#pWidget { border: 1px solid #808080; }");

    ui->stackedWidget->addWidget(widgetr);
    ui->stackedWidget->addWidget(wonlinedoc);
    ui->stackedWidget->addWidget(schedule_wid);
    ui->stackedWidget->setCurrentWidget(widgetr);

    connect(widgetfunc, &WidgetFunctional::showFiletag, this, [=] {
        ui->stackedWidget->setCurrentWidget(widgetr); });

    connect(widgetfunc, &WidgetFunctional::showwOnlinedoc, this, [=] {
        ui->stackedWidget->setCurrentWidget(wonlinedoc); });

    connect(widgetfunc, &WidgetFunctional::showWSchedule, this, [=] {
        ui->stackedWidget->setCurrentWidget(schedule_wid); });
    connect(widgetfunc, &WidgetFunctional::sendEmailForm, this, &MainWindow::receiveSendEmailForm);

    connect(widgetfunc, &WidgetFunctional::showDraw, this, [=] {
        // ui->stackedWidget->setCurrentWidget(controlFrame);
        QWidget *currentWidget = tabWidget->currentWidget();
        TabHandleIMG *tabHandleImg = qobject_cast<TabHandleIMG*>(currentWidget);
        if (tabHandleImg) {
            // tabHandleImg->showControlFrame(controlFrame);
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
    loginButton->setIcon(QIcon("://image/user.svg"));

    loginButton->setIconSize(loginButton->size());

    ui->menubar->setCornerWidget(loginButton, Qt::TopRightCorner);
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::showUserInfoDialog);


    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    connect(tabWidget, &QTabWidget::tabCloseRequested, this, [this](int index) {
        qDebug() << "Tab close requested at index: " << index;

        on_actionclose_triggered();
    });
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow),
    recentFilesManager(new RecentFilesManager(this))
{
    ui->setupUi(this);

    initSmal();
    initFunc();
    initSpli();

    connect(tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
    connect(wonlinedoc->m_csvLinkServer, &csvLinkServer::filePathSent, this, &MainWindow::handleFilePathSent);
    connect(recentFilesManager, &RecentFilesManager::fileOpened, this, &MainWindow::openFile);
    connect(file_system, &FileSystem::fileOpened, this, &MainWindow::openFile);
    connect(schedule_wid, &ScheduleWid::fileClicked, this, &MainWindow::openFile);
    connect(file_backup_list, &FileBackupList::s_fileopen, this, &MainWindow::openFile);
    recentFilesManager->populateRecentFilesMenu(ui->recentFile);

}

void MainWindow::onTabChanged(int index) {
    // qDebug() << "MainWindow::MainWindow" << index;
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
    qDebug() << "MainWindow::openFile" << filePath;

    if (fileTabMap.contains(filePath)) {
        int existingIndex = fileTabMap[filePath];
        tabWidget->setCurrentIndex(existingIndex);  // 跳转到已有标签页
        return;  // 文件已打开，直接返回
    }

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
        fileTabMap.insert(filePath, newIndex);
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
    currentTab->fileSave();
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
        return new TabHandleIMG(fileName);
    }
    else
    {
        qDebug() << "Unsupported file type:" << fileName;
        return nullptr;
    }
}


void MainWindow::on_actionclose_triggered()
{
    int currentIndex = tabWidget->currentIndex();
    if (currentIndex >= 0) {
        QWidget *widget = tabWidget->widget(currentIndex);

        if (!widget) {
            qDebug() << "No widget found at current index.";
            return;
        }
        if (dynamic_cast<SendEmail*>(widget)) {
            SendEmail *sendEmailTab = qobject_cast<SendEmail*>(widget);
            tabWidget->removeTab(currentIndex);
            delete sendEmailTab;
        }
        TabAbstract *tab = qobject_cast<TabAbstract*>(widget);
        if (tab) {
            if (tab->confirmClose())
            {
                tabWidget->removeTab(currentIndex);
                QString filePath = tab->getCurrentFilePath();
                qDebug() << "MainWindow::on_actionclose_triggered" << filePath;
                fileTabMap.remove(filePath);            }
            else
                qDebug() << "Tab close canceled by user.";
        }
    }
    else {
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




void MainWindow::on_actionshe_triggered()
{
    setiing = new Setting();
    setiing->show();
}


