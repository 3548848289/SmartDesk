#include "WFileTag.h"
#include "ui_WFileTag.h"

WidgetRU::WidgetRU(QWidget *parent)
    : QWidget(parent), ui(new Ui::WidgetRU), fileSystemModel(new QFileSystemModel(this)), dbManager(new DatabaseManager()) {
    ui->setupUi(this);

    currentDir = QDir::currentPath();
    if (!dbManager->open()) {
        qDebug() << "数据库连接失败";
    }

    fileSystemModel->setRootPath(currentDir);
    ui->treeView->setStyleSheet("QTreeView::item { height: 30px; }");
    ui->treeView->setModel(fileSystemModel);
    ui->treeView->setHeaderHidden(true);
    for (int i = 1; i < fileSystemModel->columnCount(); ++i) {
        ui->treeView->setColumnHidden(i, true);
    }
    ui->treeView->setRootIndex(fileSystemModel->index(currentDir));

    ui->pathLineEdit->setText(currentDir);

    tagItemdelegate = new TagItemDelegate(this, dbManager);
    ui->treeView->setItemDelegate(tagItemdelegate);


    connect(ui->pathLineEdit, &QLineEdit::returnPressed, this, &WidgetRU::goButtonClicked);
    connect(ui->goButton, &QPushButton::clicked, this, &WidgetRU::goButtonClicked);
    connect(ui->treeView, &QTreeView::clicked, this, &WidgetRU::onItemClicked);
    connect(tagItemdelegate, &TagItemDelegate::buttonClicked, this, &WidgetRU::handleButtonClicked);

}

void WidgetRU::handleButtonClicked(const QModelIndex &index)
{
    qDebug() << "Button clicked at index:" << index;
}
void WidgetRU::onItemClicked(const QModelIndex &index) {
    if (fileSystemModel->isDir(index))
        return;

    curfilePath = fileSystemModel->filePath(index);
    QStringList tags;
    QString annotation;

    int fileId;
    if (dbManager->getFileId(curfilePath, fileId)) {
        dbManager->getTags(fileId, tags);
        dbManager->getAnnotation(fileId, annotation);
    }

    ui->tagsLineEdit->setText(tags.join(", "));
    ui->annotationTextEdit->setText(annotation);

    emit fileOpened(curfilePath);
}

void WidgetRU::goButtonClicked() {
    currentDir = ui->pathLineEdit->text();
    QFileInfo fileInfo(currentDir);
    if (fileInfo.exists() && fileInfo.isDir()) {
        ui->treeView->setRootIndex(fileSystemModel->index(currentDir));
    } else {
        qDebug() << "Invalid path:" << currentDir;
    }
}

void WidgetRU::on_saveButton_clicked() {
    QString filePath = ui->treeView->currentIndex().data(QFileSystemModel::FilePathRole).toString();
    QStringList tags = ui->tagsLineEdit->text().split(", ");
    QString annotation = ui->annotationTextEdit->toPlainText();

    int fileId;
    if (!dbManager->getFileId(filePath, fileId)) {
        dbManager->addFilePath(filePath, fileId);
    }
    dbManager->saveTags(fileId, tags);
    dbManager->saveAnnotation(fileId, annotation);
}

void WidgetRU::on_newButton_clicked()
{

}

WidgetRU::~WidgetRU() {
    delete ui;
    delete dbManager;
}
