
#ifndef FILEBACKUPWID_H
#define FILEBACKUPWID_H

#include <QDialog>
#include <QFile>
#include <QDateTime>
#include <QCoreApplication>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QSettings>

namespace Ui {
class FileBackupWid;
}

class FileBackupWid : public QDialog
{
    Q_OBJECT

public:
    explicit FileBackupWid(const QString &filePath, QWidget *parent = nullptr);  // 修改构造函数
    QString getBackupFilePath() const;
    ~FileBackupWid();

private slots:

    void on_save_clicked();

private:
    Ui::FileBackupWid *ui;
    bool backupFile(const QString &filePath, const QString &fileName);
    QString m_backupFilePath; // 存储备份路径
    QString m_filePath;  // 用于保存传入的 filePath
};

#endif // FILEBACKUPWID_H
