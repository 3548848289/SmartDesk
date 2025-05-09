#include "include/FileBackupWid.h"
#include "ui/ui_FileBackupWid.h"

FileBackupWid::FileBackupWid(const QString &filePath, QWidget *parent) :QDialog(parent),ui(new Ui::FileBackupWid), m_filePath(filePath)
{
    ui->setupUi(this);

    QString timeStamp = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
    QString backupFileName = QFileInfo(filePath).baseName() + timeStamp + "." + QFileInfo(filePath).suffix();


    QSettings settings("settings.ini", QSettings::IniFormat);
    QString backupDir = settings.value("BackupDir", QCoreApplication::applicationDirPath() + "/user").toString();

    ui->edit_path->setText(backupDir);
    ui->edit_name->setText(backupFileName);
}

QString FileBackupWid::getBackupFilePath() const {
    return m_backupFilePath;
}

FileBackupWid::~FileBackupWid() {
    delete ui;
}

bool FileBackupWid::backupFile(const QString &filePath, const QString &fileName) {
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

void FileBackupWid::on_save_clicked()
{
    QString fileName = ui->edit_name->text();
    if (backupFile(m_filePath, fileName)) {
        QMessageBox::information(this, "", "文件已成功备份！");
        accept();
    } else {
        QMessageBox::critical(this, "", "备份文件失败！");
    }
}

void FileBackupWid::on_canle_clicked()
{
    this->close();
}

