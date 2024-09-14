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
        QRect iconRect(option.rect.right() - 16, option.rect.top() + 5, 16, 16);
        QIcon tagIcon(":/image/application_go.svg");
        tagIcon.paint(painter, iconRect, Qt::AlignCenter);

        // 绘制按钮
        QRect buttonRect(option.rect.right() - 90, option.rect.top() + 5, 60, option.rect.height() - 10);
        QStyleOptionButton buttonOption;
        buttonOption.rect = buttonRect;
        buttonOption.text = "增加标签";
        buttonOption.state = QStyle::State_Raised;

        QStyle *style = option.widget ? option.widget->style() : QApplication::style();
        style->drawControl(QStyle::CE_PushButton, &buttonOption, painter);
    }
}


bool TagItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        QRect buttonRect(option.rect.right() - 70, option.rect.top() + 5, 60, option.rect.height() - 10);

        if (buttonRect.contains(mouseEvent->pos())) {
            // 确保按钮点击不会触发其他点击事件
            emit buttonClicked(index);
            return true; // 返回 true，表示事件已处理
        }
    }

    // 处理其他区域的点击事件
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
