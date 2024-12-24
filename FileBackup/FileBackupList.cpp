#include "include/FileBackupList.h"
#include "ui/ui_FileBackupList.h"

FileBackupList::FileBackupList(QWidget *parent) :QWidget(parent), ui(new Ui::FileBackupList),
    serverManager(ServerManager::instance())
{
    ui->setupUi(this);
    connect(serverManager, &ServerManager::onFilesListUpdated, this, &FileBackupList::updateFileList);

}

FileBackupList::~FileBackupList()
{
    delete ui;
}

void FileBackupList::updateFileList(const QStringList& files) {
    ui->listWidget->clear();
    for (const QString& filePath : files) {
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.fileName();
        QListWidgetItem *item = new QListWidgetItem(fileName);
        item->setToolTip(filePath);
        item->setData(Qt::UserRole, filePath);
        ui->listWidget->addItem(item);
        qDebug() << "File in FileSystem:" << filePath;
    }
}

void FileBackupList::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString filePath = item->data(Qt::UserRole).toString();

    emit s_fileopen(filePath);

    file_restore_wid = new FileRestoreWid(filePath, serverManager, this);
    file_restore_wid->exec();
}
