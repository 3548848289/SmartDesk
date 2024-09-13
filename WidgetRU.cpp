#include "WidgetRU.h"
#include "ui_WidgetRU.h"


// 修改 WidgetRU 构造函数，确保内部控件的布局
WidgetRU::WidgetRU(QWidget *parent) : QWidget(parent), ui(new Ui::WidgetRU), fileSystemModel(new QFileSystemModel(this))
{
    ui->setupUi(this);

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


    fileSystemModel->setRootPath("D:/QT6/Qt_pro/202406Train/mytxt");
    ui->treeView->setModel(fileSystemModel);
    ui->treeView->setHeaderHidden(true);
    for (int i = 1; i < fileSystemModel->columnCount(); ++i) {
        ui->treeView->setColumnHidden(i, true);
    }
    ui->treeView->setRootIndex(fileSystemModel->index("D:/QT6/Qt_pro/202406Train/mytxt"));
    ui->pathLineEdit->setText("D:/QT6/Qt_pro/202406Train/mytxt");

    ui->treeView->setItemDelegate(new TagItemDelegate(this, db));

    connect(ui->pathLineEdit, &QLineEdit::returnPressed, this, &WidgetRU::goButtonClicked);
    connect(ui->goButton, &QPushButton::clicked, this, &WidgetRU::goButtonClicked);
    connect(ui->treeView, &QTreeView::clicked, this, &WidgetRU::onItemClicked);

    setLayout(ui->verticalLayout);
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
    QString filePath = fileSystemModel->filePath(index);
    emit fileOpened(filePath);


    QSqlQuery query;

    query.prepare("SELECT id FROM FilePaths WHERE file_path = :filePath");
    query.bindValue(":filePath", filePath);
    query.exec();

    int fileId = -1;
    if (query.next()) {
        fileId = query.value(0).toInt();
    } else {
        query.prepare("INSERT INTO FilePaths (file_path) VALUES (:filePath)");
        query.bindValue(":filePath", filePath);
        query.exec();
        fileId = query.lastInsertId().toInt();
    }

    query.prepare("SELECT tag_name FROM Tags WHERE file_id = :fileId");
    query.bindValue(":fileId", fileId);
    query.exec();

    QStringList tags;
    while (query.next()) {
        tags << query.value(0).toString();
    }

    query.prepare("SELECT annotation FROM Annotations WHERE file_id = :fileId");
    query.bindValue(":fileId", fileId);
    query.exec();

    QString annotation;
    if (query.next()) {
        annotation = query.value(0).toString();
    }


    ui->tagsLineEdit->setText(tags.join(", "));
    ui->annotationTextEdit->setPlainText(annotation);
}
void WidgetRU::saveMetadata(const QString &filePath, const QStringList &tags, const QString &annotation)
{
    QSqlQuery query;

    // 查找文件路径对应的 ID
    query.prepare("SELECT id FROM FilePaths WHERE file_path = :filePath");
    query.bindValue(":filePath", filePath);
    query.exec();

    int fileId = -1;
    if (query.next()) {
        fileId = query.value(0).toInt();
    }

    if (fileId == -1) {
        qDebug() << "文件路径未找到";
        return;
    }

    // 保存标签
    query.prepare("DELETE FROM Tags WHERE file_id = :fileId");
    query.bindValue(":fileId", fileId);
    query.exec();

    for (const QString &tag : tags) {
        query.prepare("INSERT INTO Tags (file_id, tag_name) VALUES (:fileId, :tagName)");
        query.bindValue(":fileId", fileId);
        query.bindValue(":tagName", tag);
        query.exec();
    }

    // 保存批注
    query.prepare("INSERT OR REPLACE INTO Annotations (file_id, annotation) VALUES (:fileId, :annotation)");
    query.bindValue(":fileId", fileId);
    query.bindValue(":annotation", annotation);
    query.exec();
}


void WidgetRU::goButtonClicked() {
    QString path = ui->pathLineEdit->text();
    QFileInfo fileInfo(path);
    if (fileInfo.exists() && fileInfo.isDir()) {
        ui->treeView->setRootIndex(fileSystemModel->index(path));
    } else {
        qDebug() << "Invalid path:" << path;
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

