#ifndef FILERESTOREWID_H
#define FILERESTOREWID_H

#include <QDialog>
#include <QString>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include "../../manager/include/ServerManager.h"
#include "../../manager/include/dbService.h"

namespace Ui {
class FileRestoreWid;
}

class FileRestoreWid : public QDialog
{
    Q_OBJECT

public:
    explicit FileRestoreWid(QString fileName, ServerManager* serverManager, QWidget *parent = nullptr);
    ~FileRestoreWid();

private slots:
    void on_pathBtn_clicked();

    void on_saveasBtn_clicked();

    void on_restoreBtn_clicked();

private:
    Ui::FileRestoreWid *ui;
    QString file_name;          //备份文件全文件路径
    QString backup_filepath;    //备份文件路径
    QDateTime submit_time;
    QString initial_file_name;  //原文件全文件路径
    ServerManager* serverManager;
    dbService& dbservice;

};

#endif // FILERESTOREWID_H
