#include "WidgetRU.h"
#include "ui_WidgetRU.h"

WidgetRU::WidgetRU(QWidget *parent) :QWidget(parent),ui(new Ui::WidgetRU),
    treeView(new QTreeView(this)), fileSystemModel(new QFileSystemModel(this))
{
    ui->setupUi(this);
    fileSystemModel->setRootPath(QDir::rootPath());
    treeView->setModel(fileSystemModel);
    treeView->setRootIndex(fileSystemModel->index(QDir::homePath()));
}

WidgetRU::~WidgetRU()
{
    delete ui;
}
