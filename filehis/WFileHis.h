#ifndef WFILEHIS_H
#define WFILEHIS_H

#include <QWidget>
#include <QListWidgetItem>

#include "DPull.h"
#include "../manager/ServerManager.h"

namespace Ui {
class WFileHis;
}

class WFileHis : public QWidget
{
    Q_OBJECT

public:
    explicit WFileHis(QWidget *parent = nullptr);
    ~WFileHis();
private slots:
    void updateFileList(const QStringList& files);

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    ServerManager* serverManager;
    DPull * dpull;
    Ui::WFileHis *ui;
};

#endif // WFILEHIS_H
