#include "./include/WFileTag.h"
#include "ui/ui_WFileTag.h"

WFileTag::WFileTag(DBSQlite * dbsqlite, QWidget *parent)
    : QWidget(parent), ui(new Ui::WFileTag), serverManager(ServerManager::instance()),
    fileSystemModel(new QFileSystemModel(this)), dbsqlite(dbsqlite)
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

    tagItemdelegate = new TagItemDelegate(this, serverManager);
    ui->treeView->setItemDelegate(tagItemdelegate);

    connect(ui->pathLineEdit, &QLineEdit::returnPressed, this, &WFileTag::goButtonClicked);
    connect(ui->goButton, &QPushButton::clicked, this, &WFileTag::goButtonClicked);
    connect(ui->treeView, &QTreeView::clicked, this, &WFileTag::onItemClicked);

    connect(tagItemdelegate, &TagItemDelegate::tagbutClicked, this, [this](const QModelIndex &index) {
        qDebug() << "点击了添加标签按钮";
    });
    connect(tagItemdelegate, &TagItemDelegate::subbutClicked, this, [this](const QModelIndex &index) {
        qDebug() << "点击了提交记录按钮";

    });

}



void WFileTag::onItemClicked(const QModelIndex &index) {
    if (fileSystemModel->isDir(index) || tagItemdelegate->isButtonClicked) {
        tagItemdelegate->isButtonClicked = false;
        return;
    }

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
}
