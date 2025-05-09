#include "include/FileRestoreWid.h"
#include "ui/ui_FileRestoreWid.h"

FileRestoreWid::FileRestoreWid(QString fileName, bool isMissing, QWidget *parent) :QDialog(parent),
    ui(new Ui::FileRestoreWid), file_name(fileName), isMissing(isMissing),
    dbservice(dbService::instance("./SmartDesk.db")) {
    ui->setupUi(this);
    QFileInfo tmp(fileName);
    backup_filepath = tmp.path();

    submit_time = dbservice.dbBackup().getSubTime(fileName);
    initial_file_name = dbservice.dbBackup().getInitPath(fileName);

    ui->dateTimeEdit->setDateTime(submit_time);
    ui->filenameEdit->setText(file_name);
    ui->initpathEdit->setText(initial_file_name);
    QPixmap pixmap(":/usedimage/tips.svg");

    QSize labelSize = ui->label_4->size();
    QPixmap scaledPixmap = pixmap.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->label_4->setPixmap(scaledPixmap);
    if(isMissing) {
        ui->label_4->show();
        ui->label_4->setToolTip("文件已经缺失，可在上一级窗口右键文件更改路径");
    }
    else
        ui->label_4->hide();
}

FileRestoreWid::~FileRestoreWid()
{
    delete ui;
}

bool FileRestoreWid::copyFileSafely(const QString &source, const QString &destination, QString *errorMsg)
{
    QFileInfo sourceInfo(source);
    if (!sourceInfo.exists()) {
        if (errorMsg) *errorMsg = "源文件不存在!";
        return false;
    }

    QFileInfo destInfo(destination);
    QDir destDir = destInfo.absoluteDir();

    if (!destDir.exists()) {
        if (!destDir.mkpath(".")) {
            if (errorMsg) *errorMsg = "无法创建目标目录!";
            return false;
        }
    }

    if (destInfo.exists() && !QFile::remove(destination)) {
        if (errorMsg) *errorMsg = "无法删除已有目标文件!";
        return false;
    }

    if (!QFile::copy(source, destination)) {
        if (errorMsg) *errorMsg = "文件复制失败!";
        return false;
    }

    return true;
}

void FileRestoreWid::on_saveasBtn_clicked()
{
    QString suggestedName = QFileInfo(file_name).fileName();
    QString savePath = QFileDialog::getSaveFileName(
        this, tr("另存为"), QDir::homePath() + "/" + suggestedName, tr("所有文件 (*.*)"));

    if (savePath.isEmpty())
        return;

    QString error;
    if (!copyFileSafely(file_name, savePath, &error)) {
        QMessageBox::warning(this, "", error);
        return;
    }

    QMessageBox::information(this, "", "文件另存成功!");
}

void FileRestoreWid::on_restoreBtn_clicked()
{
    QString error;
    QString targetFilePath = ui->initpathEdit->text();

    if (!copyFileSafely(file_name, targetFilePath, &error)) {
        QMessageBox::warning(this, "", error);
        return;
    }

    QMessageBox::information(this, "", "文件恢复成功!");
}
