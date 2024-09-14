#ifndef TAGITEMDELEGATE_H
#define TAGITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QPainter>
#include <QApplication>
#include <QStyleOptionButton>
#include <QMouseEvent>
#include <QStyle>
#include <QFileSystemModel>
#include <QMenu>
#include <QAction>

class TagItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

signals:
    void buttonClicked(const QModelIndex &index);
    void openFileRequested(const QString &filePath);
    void deleteFileRequested(const QString &filePath);

public:
    explicit TagItemDelegate(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;


    void showContextMenu(const QPoint &pos, const QModelIndex &index, QAbstractItemModel *model);

private:
    QSqlDatabase m_db;
    bool hasTags(const QString &filePath) const;
};

#endif // TAGITEMDELEGATE_H
