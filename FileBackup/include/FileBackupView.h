#ifndef FileBackupView_H
#define FileBackupView_H

#include <QWidget>
#include <QListWidgetItem>
#include <QMenu>

#include "FileRestoreWid.h"
#include "../../manager/include/dbService.h"
#include "../../manager/include/ServerManager.h"

namespace Ui {
class FileBackupView;
}

class FileBackupView : public QWidget
{
    Q_OBJECT

public:
    explicit FileBackupView(QWidget *parent = nullptr);
    ~FileBackupView();

    bool deleteBackupFile(const QString &backupFilePath);
public slots:
    void updateFileList(const QString filepath);

private slots:
    void on_backupList_itemClicked(QListWidgetItem *item);
    void on_fileListComboBox_currentIndexChanged(int index);


    void on_pushButton_clicked();

    void on_backupList_customContextMenuRequested(const QPoint &pos);

signals:
    void s_fileopen(const QString& filepath);

private:
    ServerManager* serverManager;
    dbService& dbservice;
    FileRestoreWid * file_restore_wid;
    Ui::FileBackupView *ui;
    QList<QString> missingFiles;

    QString choosed_file;

    void loadFileNames();
};

#endif // FileBackupView_H
