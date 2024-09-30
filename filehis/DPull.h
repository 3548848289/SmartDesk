#ifndef DPULL_H
#define DPULL_H

#include <QDialog>
#include <QString>
#include "../manager/ServerManager.h"

namespace Ui {
class DPull;
}

class DPull : public QDialog
{
    Q_OBJECT

public:
    explicit DPull(QString fileName, ServerManager* serverManager, QWidget *parent = nullptr);
    ~DPull();

private slots:
    void on_fastDlBtn_clicked();

    void on_dlBtn_clicked();

private:
    Ui::DPull *ui;
    QString fileName;
    ServerManager* serverManager;
};

#endif // DPULL_H
