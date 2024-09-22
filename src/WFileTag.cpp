#include "WFileTag.h"
#include "../ui/ui_WFileTag.h"

WFileTag::WFileTag(DatabaseManager * dbManager, QWidget *parent)
    : QWidget(parent), ui(new Ui::WFileTag),
    fileSystemModel(new QFileSystemModel(this)), dbManager(dbManager)
{
    ui->setupUi(this);
    currentDir = "D:/QT6/Qt_pro/project/mytxt";
    fileSystemModel->setRootPath(currentDir);
    ui->treeView->setStyleSheet("QTreeView::item { height: 30px; }");
    ui->treeView->setModel(fileSystemModel);
    ui->treeView->setHeaderHidden(true);
    for (int i = 1; i < fileSystemModel->columnCount(); ++i) {
        ui->treeView->setColumnHidden(i, true);
    }
    ui->treeView->setRootIndex(fileSystemModel->index(currentDir));

    ui->pathLineEdit->setText(currentDir);

    serverManager = new ServerManager(); // 初始化 ServerManager
    tagItemdelegate = new TagItemDelegate(this, dbManager, serverManager);
    ui->treeView->setItemDelegate(tagItemdelegate);

    connect(ui->pathLineEdit, &QLineEdit::returnPressed, this, &WFileTag::goButtonClicked);
    connect(ui->goButton, &QPushButton::clicked, this, &WFileTag::goButtonClicked);
    connect(ui->treeView, &QTreeView::clicked, this, &WFileTag::onItemClicked);
    connect(tagItemdelegate, &TagItemDelegate::buttonClicked, this, &WFileTag::handleButtonClicked);

    connect(serverManager, &ServerManager::onFilesListUpdated, this, &WFileTag::updateFileList);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &WFileTag::listItemClicked);

}

void WFileTag::listItemClicked(QListWidgetItem* item) {
    QString fileName = item->text();
    qDebug() << "Downloading file:" << fileName;
    serverManager->downloadFile(fileName);
}

void WFileTag::handleButtonClicked(const QModelIndex &index)
{
    qDebug() << "Button clicked at index:" << index;
}

void WFileTag::updateFileList(const QStringList& files) {
    qDebug() << "WFileTag:";
    for (const QString& file : files) {
        ui->listWidget->addItem(file);
        qDebug() << "File in WFileTag:" << file;
    }

}

void WFileTag::onItemClicked(const QModelIndex &index) {
    if (fileSystemModel->isDir(index))
        return;

    QString curfilePath = fileSystemModel->filePath(index);
    QString directoryPath = QFileInfo(curfilePath).absolutePath();

    qDebug() << "----WFileTag File Path:" << curfilePath;
    qDebug() << "----WFileTag Directory Path:" << directoryPath;

    currentDir = directoryPath;
    serverManager->setCurdir(currentDir);

    emit fileOpened(curfilePath);
}


void WFileTag::goButtonClicked() {
    currentDir = ui->pathLineEdit->text();
    QFileInfo fileInfo(currentDir);
    if (fileInfo.exists() && fileInfo.isDir()) {
        ui->treeView->setRootIndex(fileSystemModel->index(currentDir));
    } else {
        qDebug() << "Invalid path:" << currentDir;
    }
}



WFileTag::~WFileTag() {
    delete ui;
    delete dbManager;
}
