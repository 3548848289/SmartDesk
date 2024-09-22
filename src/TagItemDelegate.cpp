#include "TagItemDelegate.h"

TagItemDelegate::TagItemDelegate(QObject *parent, DatabaseManager *dbManager, ServerManager *serverManager)
    : QStyledItemDelegate(parent), m_dbManager(dbManager), serverManager(serverManager) {


}


void TagItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);

    QString filePath = index.data(QFileSystemModel::FilePathRole).toString();

    if (hasTags(filePath)) {
        QRect iconRect(option.rect.right() - 30, option.rect.top() + 5, 20, 20);
        QIcon tagIcon(":/usedimage/edittag.svg");
        tagIcon.paint(painter, iconRect, Qt::AlignCenter);
    }
    if (m_dbManager.hasSubmissions(filePath)) {
        QRect submissionIconRect(option.rect.right() - 60, option.rect.top() + 5, 20, 20);
        QIcon submissionIcon(":/usedimage/submission.svg");
        submissionIcon.paint(painter, submissionIconRect, Qt::AlignCenter);
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
    auto it = m_tagsCache.find(filePath);
    if (it != m_tagsCache.end())
        return it.value();

    bool hasTags = m_dbManager && m_dbManager->hasTagsForFile(filePath);
    const_cast<TagItemDelegate*>(this)->m_tagsCache[filePath] = hasTags;
    return hasTags;
}


void TagItemDelegate::showContextMenu(const QPoint &pos, const QModelIndex &index, QAbstractItemModel *model) {
    QMenu contextMenu;
    QAction *openAction = new QAction("打开文件", &contextMenu);
    QAction *deleteAction = new QAction("删除文件", &contextMenu);
    QAction *newtag = new QAction("新建标签", &contextMenu);
    QAction *commit = new QAction("提交远程", &contextMenu);
    QAction *history = new QAction("提交历史", &contextMenu);

    connect(newtag, &QAction::triggered, [this, index, model]() {
       DTag tagDialog;
        if (tagDialog.exec() == QDialog::Accepted) {
            QStringList tagName = tagDialog.getTagName();
            QString annotation = tagDialog.getAnnotation();
            QDateTime expirationDate = tagDialog.getExpirationDate();

            QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();

            int fileId;
            if (!m_dbManager->getFileId(filePath, fileId)) {
                m_dbManager->addFilePath(filePath, fileId);
            }
            m_dbManager->saveTags(fileId, tagName);
            m_dbManager->saveAnnotation(fileId, annotation);
            m_dbManager->saveExpirationDate(fileId, expirationDate);
        }
    });

    connect(openAction, &QAction::triggered, [this, index, model]() {
        QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();
        emit openFileRequested(filePath);
    });

    connect(deleteAction, &QAction::triggered, [this, index, model]() {
        QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();
        emit deleteFileRequested(filePath);
    });

    connect(commit, &QAction::triggered, [this, index, model]() {
        serverManager->commitToServer(index, model);
        QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();;
        m_dbManager->recordSubmission(filePath);
    });

    connect(history, &QAction::triggered, [this, index, model]() {
        this->serverManager->getFilesInDirectory(index, model);

    });

    contextMenu.addAction(openAction);
    contextMenu.addAction(deleteAction);
    contextMenu.addAction(newtag);
    contextMenu.addAction(commit);
    contextMenu.addAction(history);

    // 在指定位置显示菜单
    contextMenu.exec(pos);
}

