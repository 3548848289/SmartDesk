#include "WidgetRU.h"
#include "ui_WidgetRU.h"
#include<QSplitter>

WidgetRU::WidgetRU(QWidget *parent) : QWidget(parent), ui(new Ui::WidgetRU), fileSystemModel(new QFileSystemModel(this))
{
    ui->setupUi(this);

    currentDir = QDir::currentPath();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("file_metadata.db");

    if (!db.open()) {
        qDebug() << "数据库连接失败：" << db.lastError().text();
    } else {
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS FilePaths (id INTEGER PRIMARY KEY, file_path TEXT UNIQUE)");
        query.exec("CREATE TABLE IF NOT EXISTS Tags (id INTEGER PRIMARY KEY, file_id INTEGER, tag_name TEXT, FOREIGN KEY(file_id) REFERENCES FilePaths(id))");
        query.exec("CREATE TABLE IF NOT EXISTS Annotations (id INTEGER PRIMARY KEY, file_id INTEGER, annotation TEXT, FOREIGN KEY(file_id) REFERENCES FilePaths(id))");
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
    tagItemdelegate = new TagItemDelegate(this, db);
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

void WidgetRU::onItemClicked(const QModelIndex &index)
{

    if (fileSystemModel->isDir(index))
        return;

    curfilePath = fileSystemModel->filePath(index);

    QStringList tags;
    QString annotation;
    getFileMetadata(curfilePath, tags, annotation);

    ui->tagsLineEdit->setText(tags.join(", "));
    ui->annotationTextEdit->setText(annotation);

    emit fileOpened(curfilePath);

}
void WidgetRU::getFileMetadata(const QString &filePath, QStringList &tags, QString &annotation)
{
    // 首先查询文件路径对应的 file_id
    QSqlQuery query;
    query.prepare("SELECT id FROM FilePaths WHERE file_path = :file_path");
    query.bindValue(":file_path", filePath);

    if (query.exec() && query.next()) {
        int fileId = query.value(0).toInt();

        // 查询文件对应的标签
        QSqlQuery tagQuery;
        tagQuery.prepare("SELECT tag_name FROM Tags WHERE file_id = :file_id");
        tagQuery.bindValue(":file_id", fileId);

        if (tagQuery.exec()) {
            while (tagQuery.next()) {
                tags.append(tagQuery.value(0).toString());
            }
        }

        // 查询文件对应的批注
        QSqlQuery annotationQuery;
        annotationQuery.prepare("SELECT annotation FROM Annotations WHERE file_id = :file_id");
        annotationQuery.bindValue(":file_id", fileId);

        if (annotationQuery.exec() && annotationQuery.next()) {
            annotation = annotationQuery.value(0).toString();
        }
    } else {
        qDebug() << "Failed to fetch file ID for path:" << filePath;
    }
}


void WidgetRU::saveMetadata(const QString &filePath, const QStringList &tags, const QString &annotation)
{
    QSqlQuery query;

    query.prepare("INSERT INTO FilePaths (file_path) VALUES (:filePath)");
    query.bindValue(":filePath", filePath);
    query.exec();
    int fileId = query.lastInsertId().toInt();

    if (fileId == -1) {
        qDebug() << "文件路径未找到";
        return;
    }

    query.prepare("DELETE FROM Tags WHERE file_id = :fileId");
    query.bindValue(":fileId", fileId);
    query.exec();

    for (const QString &tag : tags) {
        query.prepare("INSERT INTO Tags (file_id, tag_name) VALUES (:fileId, :tagName)");
        query.bindValue(":fileId", fileId);
        query.bindValue(":tagName", tag);
        query.exec();
    }

    query.prepare("INSERT OR REPLACE INTO Annotations (file_id, annotation) VALUES (:fileId, :annotation)");
    query.bindValue(":fileId", fileId);
    query.bindValue(":annotation", annotation);
    query.exec();
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

WidgetRU::~WidgetRU() {
    delete ui;
}


void WidgetRU::on_saveButton_clicked()
{
    QString filePath = ui->treeView->currentIndex().data(QFileSystemModel::FilePathRole).toString();
    QStringList tags = ui->tagsLineEdit->text().split(", ");
    QString annotation = ui->annotationTextEdit->toPlainText();

    saveMetadata(filePath, tags, annotation);
}


void WidgetRU::on_newButton_clicked()
{

}
