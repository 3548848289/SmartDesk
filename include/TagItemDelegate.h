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
#include "../manager/DatabaseManager.h"

class TagItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

signals:
    void buttonClicked(const QModelIndex &index);
    void openFileRequested(const QString &filePath);
    void deleteFileRequested(const QString &filePath);

public:
    explicit TagItemDelegate(QObject *parent = nullptr, DatabaseManager *dbManager = nullptr);  // 使用DatabaseManager替代QSqlDatabase
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void showContextMenu(const QPoint &pos, const QModelIndex &index, QAbstractItemModel *model);

private:
    DatabaseManager *m_dbManager;  // 用于数据库操作的DatabaseManager实例
    bool hasTags(const QString &filePath) const;  // 检查文件是否有标签
};

#endif // TAGITEMDELEGATE_H
