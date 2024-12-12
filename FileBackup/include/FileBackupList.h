#ifndef FILEBACKUPLIST_H
#define FILEBACKUPLIST_H

#include <QWidget>
#include <QListWidgetItem>

#include "FileRestoreWid.h"
#include "../../manager/include/ServerManager.h"

namespace Ui {
class FileBackupList;
}

class FileBackupList : public QWidget
{
    Q_OBJECT

public:
    explicit FileBackupList(QWidget *parent = nullptr);
    ~FileBackupList();
private slots:
    void updateFileList(const QStringList& files);

    void on_listWidget_itemClicked(QListWidgetItem *item);

signals:
    void s_fileopen(const QString& filepath);

private:

    ServerManager* serverManager;
    FileRestoreWid * file_restore_wid;
    Ui::FileBackupList *ui;
};

#endif // FILEBACKUPLIST_H
