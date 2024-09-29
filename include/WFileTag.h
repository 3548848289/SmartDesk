#ifndef WFILETAG_H
#define WFILETAG_H

#include <QWidget>
#include <QFileSystemModel>
#include <QModelIndex>
#include <QListWidgetItem>
#include "TagItemDelegate.h"
#include "../manager/DBSQlite.h"
#include "DPull.h"
namespace Ui {
class WFileTag;
}

class WFileTag : public QWidget
{
    Q_OBJECT

public:
    explicit WFileTag(DBSQlite *dbsqlite, QWidget *parent = nullptr);

    ~WFileTag();

private slots:
    void onItemClicked(const QModelIndex &index);
    void goButtonClicked();

    void updateFileList(const QStringList& files);

    void listItemClicked(QListWidgetItem* item);


signals:
    void fileOpened(const QString &filePath);

private:
    void loadFileMetadata(const QString &filePath);
    void saveExpirationDate(const QString &filePath, const QDate &expirationDate);

    ServerManager* serverManager;

    Ui::WFileTag *ui;
    QFileSystemModel *fileSystemModel;
    TagItemDelegate *tagItemdelegate;
    DBSQlite *dbsqlite;
    QString curfilePath;
    QString currentDir;

    DPull * dpull;
};

#endif // WFILETAG_H
