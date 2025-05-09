#include "include/mainwindow.h"
#include "ui/ui_mainwindow.h"
#include "../manager/include/dbService.h"

void MainWindow::initCoreWidgets() {
    loginButton = new QPushButton(this);
    loginButton->setFixedSize(26, 26);
    loginButton->setStyleSheet("border: none; border-radius: 13px;");
    loginButton->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::UserAvailable));
    loginButton->setIconSize(loginButton->size());

    ui->menubar->setCornerWidget(loginButton, Qt::TopRightCorner);
    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    tabWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tabWidget, &QTabWidget::customContextMenuRequested, this, &MainWindow::onTabContextMenuRequested);
    file_system = new FileSystem(this);
    file_backup_view = new FileBackupView(this);
    wonlinedoc = new WOnlineDoc(this);
    schedule_wid= new ScheduleWid(this);
    widgetfunc = new WidgetFunctional(this);

    ui->stackedWidget->setObjectName("pWidget");
    ui->stackedWidget->setStyleSheet("QWidget#pWidget { border: 1px solid #808080; }");
    ui->stackedWidget->addWidget(file_system);
    ui->stackedWidget->addWidget(file_backup_view);
    ui->stackedWidget->addWidget(wonlinedoc);
    ui->stackedWidget->addWidget(schedule_wid);
    ui->stackedWidget->setCurrentWidget(file_system);
}

void MainWindow::initConnect() {
    connect(widgetfunc, &WidgetFunctional::showFiletag, this, [this] {
        ui->stackedWidget->setCurrentWidget(file_system); });

    connect(widgetfunc, &WidgetFunctional::showFilebackup, this, [this] {
        ui->stackedWidget->setCurrentWidget(file_backup_view); });

    connect(widgetfunc, &WidgetFunctional::showwOnlinedoc, this, [this] {
        ui->stackedWidget->setCurrentWidget(wonlinedoc); });

    connect(widgetfunc, &WidgetFunctional::showWSchedule, this, [this] {
        ui->stackedWidget->setCurrentWidget(schedule_wid); });

    connect(widgetfunc, &WidgetFunctional::sendEmailForm, this, [this](SendEmail *form) {
        int newIndex = tabWidget->addTab(form, QLatin1String("Email"));
        form->show();
        tabWidget->setCurrentIndex(newIndex);
        ui->stackedWidget->setCurrentWidget(file_system);
    });

    connect(widgetfunc, &WidgetFunctional::showClipboard, this, [this](ClipboardView* clipboard) {
        int newIndex = tabWidget->addTab(clipboard, QString("剪贴板"));
        clipboard->show();
        tabWidget->setCurrentIndex(newIndex);
        ui->stackedWidget->setCurrentWidget(file_system);
    });

    connect(widgetfunc, &WidgetFunctional::showDraw, this, [=] {
        QWidget *currentWidget = tabWidget->currentWidget();
        TabHandleIMG *tabHandleImg = qobject_cast<TabHandleIMG*>(currentWidget);
        if (tabHandleImg) {
            tabHandleImg->test();
        } else {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::warning(this, "无效的文件类型",
                "当前文件不是图片文件，是不是选取图片打开。",QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
                on_actionopen_triggered();
            else
                qDebug() << "用户取消打开图片操作";
        }
    });

    connect(loginButton, &QPushButton::clicked, this, &MainWindow::showUserInfoDialog);

    connect(tabWidget, &QTabWidget::tabCloseRequested, this, [this](int index) {
        qDebug() << "Tab close requested at index: " << index;
        on_actionclose_triggered();
    });


    connect(ui->actionhelp, &QAction::triggered, this, [this]() {
        openFile("help.txt");
    });

    connect(ui->actiondownload, &QAction::triggered, this, [this]() {
        ui->stackedWidget->setCurrentWidget(wonlinedoc);
    });

    connect(ui->actiontxt_file, &QAction::triggered, this, [this]() {
        createNewTab([]() { return new TextTab(""); }, "New Text Tab");
    });

    connect(ui->actionscv_file, &QAction::triggered, this, [this]() {
        createNewTab([]() { return new TabHandleCSV(""); }, "New CSV Tab");
    });

    connect(ui->actionxlsx_file, &QAction::triggered, this, [this]() {
        createNewTab([]() { return new TabHandleXLSX(""); }, "New XLSX Tab");
    });

    connect(ui->actionshe, &QAction::triggered, this, [this]() {
        Setting *setting = new Setting();
        setting->show();
    });

    connect(ui->actionh1, &QAction::triggered, this, [this]() {

    });

    connect(tabWidget, &QTabWidget::currentChanged, this, [this](int index) {
        currentIndex = index;
    });

    connect(wonlinedoc->shared_view, &SharedView::filePathSent, this, &MainWindow::handleFilePathSent);
    connect(wonlinedoc->download_view, &DownloadView::fileDownloaded, this, &MainWindow::handleFileDownload);
    connect(recentFilesManager, &RecentFilesManager::fileOpened, this, &MainWindow::openFile);
    connect(file_system, &FileSystem::fileOpened, this, &MainWindow::openFile);
    connect(schedule_wid, &ScheduleWid::fileClicked, this, &MainWindow::openFile);
    connect(file_backup_view, &FileBackupView::s_fileopen, this, &MainWindow::openFile);

    connect(file_system, &FileSystem::tagopened, this, [=]{
        ui->stackedWidget->setCurrentWidget(schedule_wid);
    });
    connect(file_system, &FileSystem::filebackuplistOpened, this, [=]{
        ui->stackedWidget->setCurrentWidget(file_backup_view);
    });
}

void MainWindow::initMemubarLayout() {
    QSplitter *horizontalSplitter = new QSplitter(Qt::Horizontal);
    horizontalSplitter->addWidget(widgetfunc);
    horizontalSplitter->addWidget(tabWidget);
    horizontalSplitter->addWidget(ui->combinedWidget);
    horizontalSplitter->setStretchFactor(0, 0);
    horizontalSplitter->setStretchFactor(1, 1);
    horizontalSplitter->setStretchFactor(2, 3);
    setCentralWidget(horizontalSplitter);
    QList<int> sizes = {60, 600, 340};
    horizontalSplitter->setSizes(sizes);


    const QMap<int, QString> buttonNames = {
        {1, "文件标签"}, {2, "文件备份"}, {3, "备忘日程"}, {4, "在线文档"}, {5, "手写绘图"},
        {6, "邮件服务"}, {7, "剪切字板"}, {8, "用户登录"}, {9, "更多功能"}
    };
    connect(widgetfunc, &WidgetFunctional::buttonVisibilityChanged,
            this, [this, buttonNames](int buttonIndex, bool isVisible) {
                QAction *action = findChild<QAction*>(QString("Function%1").arg(buttonIndex));
                if (action && buttonNames.contains(buttonIndex)) {
                    const QString &name = buttonNames.value(buttonIndex);
                    action->setText((isVisible ? "关闭" : "打开") + name);
                }
            });

    for (int i = 1; i <= 9; ++i) {
        QAction *action = findChild<QAction *>(QString("Function%1").arg(i));
        if (action) {
            connect(action, &QAction::triggered, this, [this, i]() {
                widgetfunc->toggleButtonVisibility(i);
            });
        }
    }

}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow),
    recentFilesManager(new RecentFilesManager(this))
{
    ui->setupUi(this);
    initCoreWidgets();
    initConnect();
    initMemubarLayout();
    openFile("help.txt");
    recentFilesManager->populateRecentFilesMenu(ui->recentFile);
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
        QMessageBox::StandardButton reply =
            QMessageBox::question(this, "未登录", "您尚未登录，是否现在登录？\n(目前没开放登录功能)",
            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes
        );
        if (reply == QMessageBox::Yes)
            widgetfunc->on_pushButton_7_clicked();
    }
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
    if (fileTabMap.contains(filePath)) {
        int existingIndex = fileTabMap[filePath];
        tabWidget->setCurrentIndex(existingIndex);
        return;
    }

    TabAbstract* newTab = createTabByFileName(filePath);
    if (newTab) {
        newTab->loadFromFile(filePath);
        QFileInfo fileInfo(filePath);
        QString baseName = fileInfo.fileName();

        int newIndex = tabWidget->addTab(newTab, baseName);
        connect(newTab, &TabAbstract::contentModified, this, [this, newIndex, baseName]() {
            if (!tabWidget->tabText(newIndex).endsWith("*"))
                tabWidget->setTabText(newIndex, baseName + "*");
        });
        connect(newTab, &TabAbstract::contentSaved, this, [this, newIndex, baseName]() {
            tabWidget->setTabText(newIndex, QFileInfo(baseName).fileName());
        });

        fileTabMap.insert(filePath, newIndex);
        tabWidget->setCurrentIndex(newIndex);

        recentFilesManager->addFile(filePath);
        recentFilesManager->populateRecentFilesMenu(ui->recentFile);
    } else
        QMessageBox::warning(this, tr("错误"), tr("不支持的文件类型"));
}

void MainWindow::on_actionsave_triggered()
{
    auto currentTab = getCurrentTab<TabAbstract>();
    if (!currentTab) return;

    QString currentFilePath = currentTab->getCurrentFilePath();

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
            return;
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
    if (fileName.endsWith(".txt", Qt::CaseInsensitive) || fileName.endsWith(".cpp", Qt::CaseInsensitive) ||
        fileName.endsWith(".qrc", Qt::CaseInsensitive) || fileName.endsWith(".ini", Qt::CaseInsensitive) ||
        fileName.endsWith(".h", Qt::CaseInsensitive)) {
        return new TextTab(fileName);
    }
    else if (fileName.endsWith(".csv", Qt::CaseInsensitive)) {
        return new TabHandleCSV(fileName);
    }
    else if(fileName.endsWith(".xlsx", Qt::CaseInsensitive)) {
        return new TabHandleXLSX(fileName);
    }
    else if(fileName.endsWith(".png", Qt::CaseInsensitive) || fileName.endsWith(".jpg", Qt::CaseInsensitive) ||
            fileName.endsWith(".jpeg", Qt::CaseInsensitive) || fileName.endsWith(".bmp", Qt::CaseInsensitive)) {
        return new TabHandleIMG(fileName);
    }
    else {
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
            return;
        }
        if (dynamic_cast<ClipboardView*>(widget)) {
            ClipboardView* clipboard = qobject_cast<ClipboardView*>(widget);
            tabWidget->removeTab(currentIndex);
            return;
        }
        TabAbstract *tab = qobject_cast<TabAbstract*>(widget);
        if (tab) {
            if (tab->confirmClose())
            {
                QString filePath = tab->getCurrentFilePath();
                fileTabMap.remove(filePath);
                tabWidget->removeTab(currentIndex);
                tab->deleteLater();
            }
            else
                qDebug() << "Tab close canceled by user.";
        }
    }
    else
        qDebug() << "No tab to close.";
}

void MainWindow::handleFileDownload(const QString &fileName, const QByteArray &fileContent)
{
    TabAbstract* newTab = createTabByFileName(fileName);
    if (newTab) {
        newTab->loadFromInternet(fileContent);
        tabWidget->addTab(newTab, fileName);
    } else
        QMessageBox::warning(this, tr("错误"), tr("不支持的文件类型"));
}

void MainWindow::handleFilePathSent()
{

    createNewTab([]() { return new TabHandleCSV(""); }, "共享文档");
    auto currentTab = getCurrentTab<TabHandleCSV>();
    currentTab->setLinkStatus(true);
    wonlinedoc->shared_view->bindTab(currentTab);
}

void MainWindow::on_actionfind_triggered()
{
    auto currentTab = getCurrentTab<TabAbstract>();
    TabHandleCSV* csvTab = qobject_cast<TabHandleCSV*>(currentTab);
    if (csvTab) {
        findDialog = new FindDialog(this);

        connect(findDialog, &FindDialog::findAll, csvTab, &TabHandleCSV::findAll);
        connect(findDialog, &FindDialog::findNext, csvTab, &TabHandleCSV::findNext);
        connect(findDialog, &FindDialog::dialogClosed, csvTab, &TabHandleCSV::clearHighlight);

        findDialog->show();
        findDialog->raise();
        findDialog->activateWindow();
    }
    else {
        TextTab* textTab = qobject_cast<TextTab*>(currentTab);
        if (textTab) {
            findDialog = new FindDialog(this);

            connect(findDialog, &FindDialog::findAll, textTab, &TextTab::findAll);
            connect(findDialog, &FindDialog::findNext, textTab, &TextTab::findNext);
            connect(findDialog, &FindDialog::dialogClosed, textTab, &TextTab::clearHighlight);

            findDialog->show();
            findDialog->raise();
            findDialog->activateWindow();
        } else {
            qDebug() << "currentTab is neither a TabHandleCSV nor a TextTab!";
        }
    }
}


void MainWindow::onTabContextMenuRequested(const QPoint &pos) {
    int tabIndex = tabWidget->tabBar()->tabAt(pos);
    if (tabIndex == -1) return; // 点击空白处无效

    QMenu menu;
    QAction *closeCurrent = menu.addAction("关闭当前");
    QAction *closeOthers = menu.addAction("关闭其他");
    QAction *closeAll = menu.addAction("关闭全部");

    QAction *selectedAction = menu.exec(tabWidget->tabBar()->mapToGlobal(pos));
    if (!selectedAction) return;

    if (selectedAction == closeCurrent) {
        closeTab(tabIndex);
    } else if (selectedAction == closeOthers) {
        for (int i = tabWidget->count() - 1; i >= 0; --i) {
            if (i != tabIndex)
                closeTab(i);
        }
    } else if (selectedAction == closeAll) {
        for (int i = tabWidget->count() - 1; i >= 0; --i) {
            closeTab(i);
        }
    }
}

void MainWindow::closeTab(int index) {
    QWidget *widget = tabWidget->widget(index);
    auto *tab = qobject_cast<TabAbstract*>(widget);
    if (tab && tab->confirmClose()) {
        tabWidget->removeTab(index);
        QString filePath = tab->getCurrentFilePath();
        fileTabMap.remove(filePath);
        tab->deleteLater(); // 避免内存泄漏
    }
}


template<typename T>
T* MainWindow::getCurrentTab()
{
    QWidget* currentWidget = tabWidget->widget(currentIndex);
    T* currentTab = qobject_cast<T*>(currentWidget);
    if (!currentTab) {
        QMessageBox::warning(this, tr("错误"), tr("当前页签是无效的"));
    }
    return currentTab;
}
