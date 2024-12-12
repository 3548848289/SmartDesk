#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QWidget>
#include <QFileSystemModel>
#include <QModelIndex>
#include <QListWidgetItem>
#include "TagItemDelegate.h"
#include "../../manager/include/dbService.h"
#include "../../manager/include/ServerManager.h"

namespace Ui {
class FileSystem;
}

class FileSystem : public QWidget
{
    Q_OBJECT

public:
    explicit FileSystem(QWidget *parent = nullptr);

    ~FileSystem();

private slots:
    void onItemClicked(const QModelIndex &index);
    void goButtonClicked();


signals:
    void fileOpened(const QString &filePath);

private:
    void loadFileMetadata(const QString &filePath);
    void saveExpirationDate(const QString &filePath, const QDate &expirationDate);

    ServerManager* serverManager;

    Ui::FileSystem *ui;
    QFileSystemModel *fileSystemModel;
    TagItemDelegate *tagItemdelegate;
    QString curfilePath;
    QString currentDir;

};

#endif // FILESYSTEM_H
