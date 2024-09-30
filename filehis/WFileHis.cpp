#include "WFileHis.h"
#include "ui_WFileHis.h"

WFileHis::WFileHis(QWidget *parent) :QWidget(parent), ui(new Ui::WFileHis),
    serverManager(ServerManager::instance())
{
    ui->setupUi(this);
    connect(serverManager, &ServerManager::onFilesListUpdated, this, &WFileHis::updateFileList);

}

WFileHis::~WFileHis()
{
    delete ui;
}



void WFileHis::updateFileList(const QStringList& files) {
    for (const QString& file : files) {
        ui->listWidget->addItem(file);
        qDebug() << "File in WFileTag:" << file;
    }

}



void WFileHis::on_listWidget_itemClicked(QListWidgetItem *item)
{

    //
    //
    //
    //
    //
    //
    //数据库或服务器设计有问题，本地无法找到所提交文件对应的提交时间
    //或者是客户端无法判断文件列表的文件是何时提交的
    //
    //
    //
    //
    QString fileName = item->text();
    qDebug() << "Downloading file:" << fileName;
    dpull = new DPull(fileName, serverManager, this);
    dpull->exec();
}

