#include "include/mainwindow.h"
#include "ui/ui_mainwindow.h"
#include "../manager/include/dbService.h"
#include <QWidgetAction>
#include <QCheckBox>

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

void MainWindow::initFunc()
{

    file_system = new FileSystem(this);
    file_backup_view = new FileBackupView(file_system);
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

    connect(widgetfunc, &WidgetFunctional::showFiletag, this, [=] {
        ui->stackedWidget->setCurrentWidget(file_system); });

    connect(widgetfunc, &WidgetFunctional::showFilebackup, this, [=] {
        ui->stackedWidget->setCurrentWidget(file_backup_view); });

    connect(widgetfunc, &WidgetFunctional::showwOnlinedoc, this, [=] {
        ui->stackedWidget->setCurrentWidget(wonlinedoc); });

    connect(widgetfunc, &WidgetFunctional::showWSchedule, this, [=] {
        ui->stackedWidget->setCurrentWidget(schedule_wid); });
    connect(widgetfunc, &WidgetFunctional::sendEmailForm, this, &MainWindow::receiveSendEmailForm);

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




}

void MainWindow::initSpli()
{
    connect(widgetfunc, &WidgetFunctional::buttonVisibilityChanged,
            this, [this](int buttonIndex, bool isVisible) {
                QAction *action = findChild<QAction*>(QString("Function%1").arg(buttonIndex));
                if (action) {
                    QString text;
                    switch (buttonIndex) {
                    case 1: text = isVisible ? "关闭文件标签" : "打开文件标签"; break;
                    case 2: text = isVisible ? "关闭文件备份" : "打开文件备份"; break;
                    case 3: text = isVisible ? "关闭备忘日程" : "打开备忘日程"; break;
                    case 4: text = isVisible ? "关闭在线文档" : "打开在线文档"; break;
                    case 5: text = isVisible ? "关闭手写绘图" : "打开手写绘图"; break;
                    case 6: text = isVisible ? "关闭邮件服务" : "打开邮件服务"; break;
                    case 7: text = isVisible ? "关闭用户登录" : "打开用户登录"; break;
                    case 8: text = isVisible ? "关闭更多功能" : "打开更多功能"; break;
                    default: return;
                    }
                    action->setText(text);
                }
    });
    connect(ui->Function1, &QAction::triggered, this, [=]() { toggleButtonVisibility(1); });
    connect(ui->Function2, &QAction::triggered, this, [=]() { toggleButtonVisibility(2); });
    connect(ui->Function3, &QAction::triggered, this, [=]() { toggleButtonVisibility(3); });
    connect(ui->Function4, &QAction::triggered, this, [=]() { toggleButtonVisibility(4); });
    connect(ui->Function5, &QAction::triggered, this, [=]() { toggleButtonVisibility(5); });
    connect(ui->Function6, &QAction::triggered, this, [=]() { toggleButtonVisibility(6); });
    connect(ui->Function7, &QAction::triggered, this, [=]() { toggleButtonVisibility(7); });
    connect(ui->Function8, &QAction::triggered, this, [=]() { toggleButtonVisibility(8); });


    QSplitter *horizontalSplitter = new QSplitter(Qt::Horizontal);
    horizontalSplitter->addWidget(widgetfunc);
    horizontalSplitter->addWidget(tabWidget);
    horizontalSplitter->addWidget(ui->combinedWidget);

    horizontalSplitter->setStretchFactor(0, 0);
    horizontalSplitter->setStretchFactor(1, 1);
    horizontalSplitter->setStretchFactor(2, 3);

    setCentralWidget(horizontalSplitter);

    QList<int> sizes;
    sizes <<  60 << 500 << 240;
    horizontalSplitter->setSizes(sizes);
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow),
    recentFilesManager(new RecentFilesManager(this))
{
    ui->setupUi(this);
    initSmal();
    initFunc();
    initSpli();

    connect(tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
    connect(wonlinedoc->shared_view, &SharedView::filePathSent, this, &MainWindow::handleFilePathSent);
    connect(recentFilesManager, &RecentFilesManager::fileOpened, this, &MainWindow::openFile);
    connect(file_system, &FileSystem::fileOpened, this, &MainWindow::openFile);

    connect(file_system, &FileSystem::filebackuplistOpened, this, [=]{
        ui->stackedWidget->setCurrentWidget(file_backup_view);
    });

    connect(schedule_wid, &ScheduleWid::fileClicked, this, &MainWindow::openFile);
    connect(file_backup_view, &FileBackupView::s_fileopen, this, &MainWindow::openFile);

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

    ui->stackedWidget->setCurrentWidget(file_system);

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
            qDebug() << baseName;

            if (!tabWidget->tabText(newIndex).endsWith("*")) {
                tabWidget->setTabText(newIndex, baseName + "*");
            }
        });

        connect(newTab, &TabAbstract::contentSaved, this, [this, newIndex, baseName]() {
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
    if (fileName.endsWith(".txt", Qt::CaseInsensitive) ||
        fileName.endsWith(".cpp", Qt::CaseInsensitive) ||
        fileName.endsWith(".qrc", Qt::CaseInsensitive) ||
        fileName.endsWith(".ini", Qt::CaseInsensitive) ||
        fileName.endsWith(".h", Qt::CaseInsensitive))
    {
        return new TextTab(fileName);  // 使用带路径的构造函数
    }
    else if (fileName.endsWith(".csv", Qt::CaseInsensitive) ||
             fileName.endsWith(".xlsx", Qt::CaseInsensitive))
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
            return;
        }
        TabAbstract *tab = qobject_cast<TabAbstract*>(widget);
        if (tab) {
            if (tab->confirmClose())
            {
                tabWidget->removeTab(currentIndex);
                QString filePath = tab->getCurrentFilePath();
                // qDebug() << "MainWindow::on_actionclose_triggered" << filePath;
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
        DownloadView* download_view = new DownloadView();
        connect(download_view, &DownloadView::fileDownloaded, this, &MainWindow::handleFileDownload);
        download_view->show();
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

    createNewTab([]() { return new TabHandleCSV(""); }, "共享文档");
    auto currentTab = getCurrentTab<TabHandleCSV>();
    currentTab->setLinkStatus(true);
    wonlinedoc->shared_view->bindTab(currentTab);
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





void MainWindow::toggleButtonVisibility(int buttonIndex)
{
    widgetfunc->toggleButtonVisibility(buttonIndex);
}



