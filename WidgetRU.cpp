#include "WidgetRU.h"
#include "ui_WidgetRU.h"


WidgetRU::WidgetRU(QWidget *parent) : QWidget(parent), ui(new Ui::WidgetRU),
    fileSystemModel(new QFileSystemModel(this))
{
    ui->setupUi(this);
    fileSystemModel->setRootPath("D:/QT6/Qt_pro/202406Train/mytxt");
    ui->treeView->setModel(fileSystemModel);
    ui->treeView->setHeaderHidden(true); // 如果不需要列标题
    for (int i = 1; i < fileSystemModel->columnCount(); ++i) {
        ui->treeView->setColumnHidden(i, true);
    }
    ui->treeView->setRootIndex(fileSystemModel->index("D:/QT6/Qt_pro/202406Train/mytxt"));

    // 设置路径输入控件
    ui->pathLineEdit->setText("D:/QT6/Qt_pro/202406Train/mytxt");

    connect(ui->pathLineEdit, &QLineEdit::returnPressed, this, &WidgetRU::goButtonClicked);
    connect(ui->goButton, &QPushButton::clicked, this, &WidgetRU::goButtonClicked);
    connect(ui->treeView, &QTreeView::clicked, this, &WidgetRU::onItemClicked);
}

void WidgetRU::onItemClicked(const QModelIndex &index)
{
    if (fileSystemModel->isDir(index)) {
        return;
    }
    QString filePath = fileSystemModel->filePath(index);
    emit fileOpened(filePath);
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
