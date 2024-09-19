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

    tagItemdelegate = new TagItemDelegate(this, dbManager);
    ui->treeView->setItemDelegate(tagItemdelegate);

    connect(ui->pathLineEdit, &QLineEdit::returnPressed, this, &WFileTag::goButtonClicked);
    connect(ui->goButton, &QPushButton::clicked, this, &WFileTag::goButtonClicked);
    connect(ui->treeView, &QTreeView::clicked, this, &WFileTag::onItemClicked);
    connect(tagItemdelegate, &TagItemDelegate::buttonClicked, this, &WFileTag::handleButtonClicked);
}

void WFileTag::handleButtonClicked(const QModelIndex &index)
{
    qDebug() << "Button clicked at index:" << index;
}

void WFileTag::onItemClicked(const QModelIndex &index) {
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

void WFileTag::goButtonClicked() {
    currentDir = ui->pathLineEdit->text();
    QFileInfo fileInfo(currentDir);
    if (fileInfo.exists() && fileInfo.isDir()) {
        ui->treeView->setRootIndex(fileSystemModel->index(currentDir));
    } else {
        qDebug() << "Invalid path:" << currentDir;
    }
}

void WFileTag::on_saveButton_clicked() {
    QString filePath = ui->treeView->currentIndex().data(QFileSystemModel::FilePathRole).toString();
    QStringList tags = ui->tagsLineEdit->text().split(", ");
    QString annotation = ui->annotationTextEdit->toPlainText();

    int fileId;
    if (!dbManager->getFileId(filePath, fileId)) {
        dbManager->addFilePath(filePath, fileId);
    }

    dbManager->saveTags(fileId, tags);
    dbManager->saveAnnotation(fileId, annotation);

    // 保存到期提醒
    QDateTime expirationDateTime = ui->dateTimeEdit->dateTime();
    dbManager->saveExpirationDate(fileId, expirationDateTime);
}

WFileTag::~WFileTag() {
    delete ui;
    delete dbManager;
}
