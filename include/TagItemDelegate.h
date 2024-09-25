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
#include "../manager/DBSQlite.h"
#include "../manager/ServerManager.h"

#include "DTag.h"
class TagItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

signals:
    void tagbutClicked(const QModelIndex &index);
    void subbutClicked(const QModelIndex &index);
    void openFileRequested(const QString &filePath);
    void deleteFileRequested(const QString &filePath);

public:
    mutable bool isButtonClicked = false;
    explicit TagItemDelegate(QObject *parent = nullptr, DBSQlite *dbManager = nullptr, ServerManager *serverManager = nullptr);
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void showContextMenu(const QPoint &pos, const QModelIndex &index, QAbstractItemModel *model);

private:
    QStringList fileList;
    DBSQlite *dbsqlite;
    ServerManager *serverManager;
    mutable QMap<QString, bool> m_tagsCache;  // 标签缓存

    bool hasTags(const QString &filePath) const;  // 检查文件是否有标签
    void addTag(const QAbstractItemModel *model, const QModelIndex &index, DTag &tagDialog);

};

#endif // TAGITEMDELEGATE_H
