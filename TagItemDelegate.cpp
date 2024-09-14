#include "TagItemDelegate.h"


TagItemDelegate::TagItemDelegate(QObject *parent, QSqlDatabase db)
    : QStyledItemDelegate(parent), m_db(db)
{
}


void TagItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);

    QString filePath = index.data(QFileSystemModel::FilePathRole).toString();
    qDebug() << filePath;

    if (hasTags(filePath)) {
        // 绘制图标
        QRect iconRect(option.rect.right() - 30, option.rect.top() + 5, 20, 20);
        QIcon tagIcon(":/usedimage/edittag.svg");
        tagIcon.paint(painter, iconRect, Qt::AlignCenter);

    }
}


bool TagItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {

        }
        if (mouseEvent->button() == Qt::RightButton) {
            if (option.rect.contains(mouseEvent->pos())) {
                showContextMenu(mouseEvent->globalPos(), index, model);
                return true;
            }
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}



bool TagItemDelegate::hasTags(const QString &filePath) const
{
    QSqlQuery query(m_db);
    query.prepare("SELECT COUNT(*) FROM FilePaths WHERE file_path = :filePath");
    query.bindValue(":filePath", filePath);

    if (!query.exec()) {
        qDebug() << "Query execution error:" << query.lastError().text();
        return false;
    }
    if (query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}


void TagItemDelegate::showContextMenu(const QPoint &pos, const QModelIndex &index, QAbstractItemModel *model) {
    QMenu contextMenu;
    QAction *openAction = new QAction("Open", &contextMenu);
    QAction *deleteAction = new QAction("Delete", &contextMenu);
    QAction *newtag = new QAction("Newtag", &contextMenu);


    connect(newtag, &QAction::triggered, [this, index, model]() {

    });
    connect(openAction, &QAction::triggered, [this, index, model]() {
        QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();
        emit openFileRequested(filePath);
    });

    connect(deleteAction, &QAction::triggered, [this, index, model]() {
        QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();
        emit deleteFileRequested(filePath);
    });

    contextMenu.addAction(openAction);
    contextMenu.addAction(deleteAction);
    contextMenu.addAction(newtag);

    // 在指定位置显示菜单
    contextMenu.exec(pos);
}
