#include "DCommit.h"
#include "ui/ui_DCommit.h"
#include <QFile>
#include <QDateTime>
#include <QCoreApplication>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
DCommit::DCommit(const QString &filePath, QWidget *parent) :QDialog(parent),ui(new Ui::DCommit), m_filePath(filePath)
{
    ui->setupUi(this);

    QString timeStamp = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
    QString backupFileName = QFileInfo(filePath).baseName() + "_" + timeStamp + "." + QFileInfo(filePath).suffix();

    QString appDir = QCoreApplication::applicationDirPath();
    QString backupDir = appDir + "/../user";
    qDebug() << backupDir;
    ui->edit_path->setText(backupDir);
    ui->edit_name->setText(backupFileName);
}

QString DCommit::getBackupFilePath() const {
    return m_backupFilePath;
}


DCommit::~DCommit()
{
    delete ui;
}


bool DCommit::backupFile(const QString &filePath, const QString &fileName)
{
    QString backupDir = ui->edit_path->text();
    QDir dir(backupDir);
    if (!dir.exists())
        if (!dir.mkpath(".")) {
            QMessageBox::critical(this, "目录创建失败", "无法创建 resources 目录！");
            return false;
        }

    QString backupFilePath = backupDir + "/" + ui->edit_name->text();

    if (QFile::copy(filePath, backupFilePath)) {
        m_backupFilePath = backupFilePath;
        return true;
    } else {
        return false;
    }
}

void DCommit::on_save_clicked()
{
    QString fileName = ui->edit_name->text();
    if (backupFile(m_filePath, fileName)) {
        QMessageBox::information(this, "备份成功", "文件已成功备份！");
        accept();
    } else {
        QMessageBox::critical(this, "备份失败", "备份文件失败！");
    }
}

