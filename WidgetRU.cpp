#include "WidgetRU.h"
#include "ui_WidgetRU.h"


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

    setLayout(ui->verticalLayout);
}

void WidgetRU::handleButtonClicked(const QModelIndex &index)
{
    // 处理按钮点击事件
    qDebug() << "Button clicked at index:" << index;
}

void WidgetRU::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 4));
    QRect rect = this->rect().adjusted(0, 0, -1, -1);
    painter.drawRect(rect);
}

void WidgetRU::onItemClicked(const QModelIndex &index)
{

    if (fileSystemModel->isDir(index)) {
        return;
    }
    curfilePath = fileSystemModel->filePath(index);
    emit fileOpened(curfilePath);

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

