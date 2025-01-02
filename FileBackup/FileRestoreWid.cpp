#include "include/FileRestoreWid.h"
#include "ui/ui_FileRestoreWid.h"

FileRestoreWid::FileRestoreWid(QString fileName, QWidget *parent)
    :QDialog(parent), ui(new Ui::FileRestoreWid), file_name(fileName)
    , dbservice(dbService::instance("../SmartDesk.db"))

{
    ui->setupUi(this);

    QFileInfo tmp(fileName);
    backup_filepath = tmp.path();

    submit_time = dbservice.dbBackup().getSubTime(fileName);
    initial_file_name = dbservice.dbBackup().getInitPath(fileName);

    QFileInfo fileInfo(initial_file_name);
    QString baseName = fileInfo.fileName();

    ui->dateTimeEdit->setDateTime(submit_time);
    ui->filenameEdit->setText(baseName);
    ui->initpathEdit->setText(initial_file_name);
    ui->backupPathRdit->setText(backup_filepath);
}

FileRestoreWid::~FileRestoreWid()
{
    delete ui;
}



void FileRestoreWid::on_pathBtn_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("选择保存目录"),
                                                    QString(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty()) {
        ui->backupPathRdit->setText(dir);
    }
}


void FileRestoreWid::on_saveasBtn_clicked()
{

}

void FileRestoreWid::on_restoreBtn_clicked()
{
    QFileInfo backup_file_info(file_name);
    if (!backup_file_info.exists()) {
        QMessageBox::warning(this, "错误", "备份文件不存在!");
        return;
    }

    QFileInfo init_file_info(initial_file_name);
    QDir target_dir = init_file_info.absolutePath();

    if (!target_dir.exists()) {
        if (!target_dir.mkpath(".")) {
            QMessageBox::warning(this, "错误", "无法创建目标目录!");
            return;
        }
    }

    if (init_file_info.exists() && !QFile::remove(initial_file_name)) {
        QMessageBox::warning(this, "错误", "无法删除原文件!");
        return;
    }

    if (!QFile::copy(file_name, initial_file_name)) {
        QMessageBox::warning(this, "错误", "无法恢复备份文件!");
        return;
    }

    QMessageBox::information(this, "成功", "文件恢复成功!");
}


// serverManager->downloadFile(fileName);
