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

    QString fileName = item->text();
    emit s_fileopen(fileName);
    dpull = new DPull(fileName, serverManager, this);
    dpull->exec();
}

