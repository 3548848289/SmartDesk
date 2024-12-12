#ifndef FILERESTOREWID_H
#define FILERESTOREWID_H

#include <QDialog>
#include <QString>
#include <QFileInfo>
#include <QFileDialog>
#include "../../manager/include/ServerManager.h"

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
    void on_fastDlBtn_clicked();

    void on_dlBtn_clicked();

    void on_dlBtn_2_clicked();

private:
    Ui::FileRestoreWid *ui;
    QString fileName;
    ServerManager* serverManager;
};

#endif // FILERESTOREWID_H
