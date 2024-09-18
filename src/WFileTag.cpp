#include "WFileTag.h"
#include "../ui/ui_WFileTag.h"

WidgetRU::WidgetRU(DatabaseManager * dbManager, QWidget *parent) : QWidget(parent), ui(new Ui::WidgetRU),
    fileSystemModel(new QFileSystemModel(this)), dbManager(dbManager)
{
    ui->setupUi(this);

    // currentDir = QDir::currentPath();
    currentDir = "D:/QT6/Qt_pro/project/mytxt";
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

void WidgetRU::on_setReminderButton_clicked() {
    if (curfilePath.isEmpty()) {
        return;
    }

    QDate expirationDate = ui->dateEdit->date();
    saveExpirationDate(curfilePath, expirationDate);
}

void WidgetRU::saveExpirationDate(const QString &filePath, const QDate &expirationDate) {
    QSqlQuery query;
    query.prepare("UPDATE FilePaths SET expiration_date = :expiration_date WHERE file_path = :file_path");
    query.bindValue(":expiration_date", expirationDate);
    query.bindValue(":file_path", filePath);
    query.exec();
}


WidgetRU::~WidgetRU() {
    delete ui;
    delete dbManager;
}
