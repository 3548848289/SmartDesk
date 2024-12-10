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
    for (const QString& filePath : files) {
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.fileName();
        QListWidgetItem *item = new QListWidgetItem(fileName);
        item->setToolTip(filePath);
        item->setData(Qt::UserRole, filePath);
        ui->listWidget->addItem(item);
        qDebug() << "File in WFileTag:" << filePath;
    }
}

void WFileHis::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString filePath = item->data(Qt::UserRole).toString();

    emit s_fileopen(filePath);

    dpull = new DPull(filePath, serverManager, this);
    dpull->exec();
}
