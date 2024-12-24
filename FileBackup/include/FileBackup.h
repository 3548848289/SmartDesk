
#ifndef FILEBACKUP_H
#define FILEBACKUP_H

#include <QDialog>
#include <QFile>
#include <QDateTime>
#include <QCoreApplication>
#include <QDir>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class FileBackup;
}

class FileBackup : public QDialog
{
    Q_OBJECT

public:
    explicit FileBackup(const QString &filePath, QWidget *parent = nullptr);  // 修改构造函数
    QString getBackupFilePath() const;
    ~FileBackup();

private slots:

    void on_save_clicked();

private:
    Ui::FileBackup *ui;
    bool backupFile(const QString &filePath, const QString &fileName);
    QString m_backupFilePath; // 存储备份路径
    QString m_filePath;  // 用于保存传入的 filePath
};

#endif // FILEBACKUP_H
