#ifndef FILECONTEXTMENU_H
#define FILECONTEXTMENU_H

#include <QMenu>
#include <QAction>
#include <QFile>
#include <QDebug>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QFileSystemModel>

#include "../../manager/include/dbService.h"
#include "../../manager/include/ServerManager.h"

class FileContextMenu : public QObject
{
    Q_OBJECT

public:
    explicit FileContextMenu(ServerManager *serverManager, dbService &dbservice, QObject *parent = nullptr);
    void showContextMenu(const QPoint &pos, const QModelIndex &index, QAbstractItemModel *model);

signals:
    void openFileRequested(const QString &filePath);
    void deleteFileRequested(const QString &filePath);
    void onFilesListUpdated(const QStringList& files);

private slots:
    void onNewTagTriggered(QAbstractItemModel *model, const QModelIndex &index);
    void onOpenFileTriggered(QAbstractItemModel *model, const QModelIndex &index);
    void onDeleteFileTriggered(QAbstractItemModel *model, const QModelIndex &index);
    void onCommitTriggered(QAbstractItemModel *model, const QModelIndex &index);
    void onHistoryTriggered(QAbstractItemModel *model, const QModelIndex &index);

private:
    ServerManager *serverManager;
    dbService &dbservice;
};

#endif // FILECONTEXTMENU_H
