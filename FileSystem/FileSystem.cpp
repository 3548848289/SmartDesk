#include "include/FileSystem.h"
#include "ui/ui_FileSystem.h"

FileSystem::FileSystem(QWidget *parent)
    : QWidget(parent), ui(new Ui::FileSystem), serverManager(ServerManager::instance()),
    fileSystemModel(new QFileSystemModel(this))
{
    ui->setupUi(this);

    QString appDir = QCoreApplication::applicationDirPath();
    QDir dir(appDir);
    dir.cdUp();
    dir.cdUp();
    currentDir = dir.absolutePath();

    fileSystemModel->setRootPath(currentDir);

    QFont font = ui->treeView->font();
    font.setPointSize(12);
    ui->treeView->setFont(font);
    ui->treeView->setStyleSheet("QTreeView::item { height: 30px; }");
    ui->treeView->setModel(fileSystemModel);
    ui->treeView->setHeaderHidden(true);
    for (int i = 1; i < fileSystemModel->columnCount(); ++i) {
        ui->treeView->setColumnHidden(i, true);
    }
    ui->treeView->setRootIndex(fileSystemModel->index(currentDir));

    ui->pathLineEdit->setText(currentDir);

    tagItemdelegate = new TagItemDelegate(this, serverManager);
    ui->treeView->setItemDelegate(tagItemdelegate);

    connect(ui->pathLineEdit, &QLineEdit::returnPressed, this, &FileSystem::on_goButton_clicked);
    connect(ui->treeView, &QTreeView::clicked, this, &FileSystem::onItemClicked);

    connect(tagItemdelegate, &TagItemDelegate::TagUpdated, this, [=](){
        ui->treeView->update();
    });

    connect(tagItemdelegate, &TagItemDelegate::tagbutClicked, this, [this](const QModelIndex &index) {
        qDebug() << "点击了添加标签按钮";
    });
    connect(tagItemdelegate, &TagItemDelegate::subbutClicked, this, [this](const QModelIndex &index) {
        emit filebackuplistOpened();
    });

}



void FileSystem::onItemClicked(const QModelIndex &index) {
    if (fileSystemModel->isDir(index) || tagItemdelegate->isButtonClicked) {
        tagItemdelegate->isButtonClicked = false;
        return;
    }

    QString curfilePath = fileSystemModel->filePath(index);
    QString directoryPath = QFileInfo(curfilePath).absolutePath();

    // qDebug() << "----FileSystem File Path:" << curfilePath;
    // qDebug() << "----FileSystem Directory Path:" << directoryPath;

    currentDir = directoryPath;
    serverManager->setCurdir(currentDir);

    emit fileOpened(curfilePath);
}

void FileSystem::on_goButton_clicked()
{
    currentDir = ui->pathLineEdit->text();
    QFileInfo fileInfo(currentDir);
    if (fileInfo.exists() && fileInfo.isDir()) {
        ui->treeView->setRootIndex(fileSystemModel->index(currentDir));
    } else {
        qDebug() << "Invalid path:" << currentDir;
    }
}

FileSystem::~FileSystem() {
    delete ui;
}
