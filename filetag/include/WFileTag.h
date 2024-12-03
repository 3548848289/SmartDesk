#ifndef WFILETAG_H
#define WFILETAG_H

#include <QWidget>
#include <QFileSystemModel>
#include <QModelIndex>
#include <QListWidgetItem>
#include "TagItemDelegate.h"
#include "../../manager/include/dbService.h"
#include "../../manager/include/ServerManager.h"

namespace Ui {
class WFileTag;
}

class WFileTag : public QWidget
{
    Q_OBJECT

public:
    explicit WFileTag(QWidget *parent = nullptr);

    ~WFileTag();

private slots:
    void onItemClicked(const QModelIndex &index);
    void goButtonClicked();


signals:
    void fileOpened(const QString &filePath);

private:
    void loadFileMetadata(const QString &filePath);
    void saveExpirationDate(const QString &filePath, const QDate &expirationDate);

    ServerManager* serverManager;

    Ui::WFileTag *ui;
    QFileSystemModel *fileSystemModel;
    TagItemDelegate *tagItemdelegate;
    QString curfilePath;
    QString currentDir;

};

#endif // WFILETAG_H
