// DCommit.h

#ifndef DCOMMIT_H
#define DCOMMIT_H

#include <QDialog>

namespace Ui {
class DCommit;
}

class DCommit : public QDialog
{
    Q_OBJECT

public:
    explicit DCommit(const QString &filePath, QWidget *parent = nullptr);  // 修改构造函数
    QString getBackupFilePath() const;

    ~DCommit();

private slots:

    void on_save_clicked();

private:
    Ui::DCommit *ui;
    bool backupFile(const QString &filePath, const QString &fileName);
    QString m_backupFilePath; // 存储备份路径
    QString m_filePath;  // 用于保存传入的 filePath
};

#endif // DCOMMIT_H
