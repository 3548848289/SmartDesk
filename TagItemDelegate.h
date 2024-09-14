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

class TagItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

signals:
    void buttonClicked(const QModelIndex &index);

public:
    explicit TagItemDelegate(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

private:
    QSqlDatabase m_db;
    bool hasTags(const QString &filePath) const;
};

#endif // TAGITEMDELEGATE_H
