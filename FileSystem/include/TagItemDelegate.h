#ifndef TAGITEMDELEGATE_H
#define TAGITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QApplication>
#include <QStyleOptionButton>
#include <QMouseEvent>
#include <QStyle>
#include <QFileSystemModel>
#include <QMenu>
#include <QAction>
#include <QMap>
#include "../../manager/include/dbService.h"
#include "../../manager/include/ServerManager.h"
#include "../../FileBackup/include/FileBackup.h"
#include "../../TagSchedule/include/AddTag.h"
class TagItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

signals:
    void tagbutClicked(const QModelIndex &index);
    void subbutClicked(const QModelIndex &index);
    void openFileRequested(const QString &filePath);
    void deleteFileRequested(const QString &filePath);
    void onFilesListUpdated(const QStringList& files);

public:
    mutable bool isButtonClicked = false;
    explicit TagItemDelegate(QObject *parent = nullptr, ServerManager *serverManager = nullptr);
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void showContextMenu(const QPoint &pos, const QModelIndex &index, QAbstractItemModel *model);

private slots:
    void onNewTagTriggered(QAbstractItemModel *model, const QModelIndex &index);
    void onOpenFileTriggered(QAbstractItemModel *model, const QModelIndex &index);
    void onDeleteFileTriggered(QAbstractItemModel *model, const QModelIndex &index);
    void onCommitTriggered(QAbstractItemModel *model, const QModelIndex &index);
    void onHistoryTriggered(QAbstractItemModel *model, const QModelIndex &index);
private:
    QStringList fileList;

    ServerManager *serverManager;
    mutable QMap<QString, bool> m_tagsCache;  // 标签缓存

    bool hasTags(const QString &filePath) const;  // 检查文件是否有标签
    void addTag(const QAbstractItemModel *model, const QModelIndex &index, AddTag &tagDialog);

    dbService& dbservice;
};

#endif // TAGITEMDELEGATE_H
