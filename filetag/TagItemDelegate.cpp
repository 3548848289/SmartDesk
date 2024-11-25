#include "./include/TagItemDelegate.h"

// TagItemDelegate.cpp
TagItemDelegate::TagItemDelegate(QObject *parent, ServerManager *serverManager)
    : QStyledItemDelegate(parent),
    dbsqlite(DBSQlite::instance()),  // 单例模式获取 DBSQlite 引用
    dbmysql(DBMySQL::instance()),    // 单例模式获取 DBMysql 引用
    serverManager(serverManager) {}



void TagItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);

    QString filePath = index.data(QFileSystemModel::FilePathRole).toString();

    if (hasTags(filePath)) {
        QRect iconRect(option.rect.right() - 30, option.rect.top() + 5, 20, 20);
        QIcon tagIcon(":/usedimage/edittag.svg");
        tagIcon.paint(painter, iconRect, Qt::AlignCenter);
    }
    if (dbmysql.hasSubmissions(filePath)) {
        QRect submissionIconRect(option.rect.right() - 60, option.rect.top() + 5, 20, 20);
        QIcon submissionIcon(":/usedimage/history.svg");
        submissionIcon.paint(painter, submissionIconRect, Qt::AlignCenter);
    }
}

bool TagItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

        QRect tagIconRect(option.rect.right() - 30, option.rect.top() + 5, 20, 20);
        if (tagIconRect.contains(mouseEvent->pos())) {
            DTag tagDialog;
            addTag(model, index, tagDialog);
            isButtonClicked = true;
            emit tagbutClicked(index);
            return true;
        }

        QRect submissionButtonRect(option.rect.right() - 60, option.rect.top() + 5, 20, 20);
        if (submissionButtonRect.contains(mouseEvent->pos())) {
            isButtonClicked = true;
            this->serverManager->getFilesInDirectory(index, model);
            emit subbutClicked(index);

            return true;
        }
    }

    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::RightButton && option.rect.contains(mouseEvent->pos())) {
            showContextMenu(mouseEvent->globalPos(), index, model);
            return true;
        }
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}


bool TagItemDelegate::hasTags(const QString &filePath) const
{
    auto it = m_tagsCache.find(filePath);
    if (it != m_tagsCache.end())
        return it.value();

    bool hasTags = dbsqlite.hasTagsForFile(filePath);
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
        addTag(model, index, tagDialog);

    });

    connect(openAction, &QAction::triggered, [this, index, model]() {
        QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();
        emit openFileRequested(filePath);
    });

    connect(deleteAction, &QAction::triggered, [this, index, model]() {
        QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();
        QFile file(filePath);
        if (file.remove()) {
            qDebug() << "文件已删除:" << filePath;
            model->removeRow(index.row());
        } else {
            qWarning() << "删除文件失败:" << filePath << "错误:" << file.errorString();
        }
        emit deleteFileRequested(filePath);
    });

    connect(commit, &QAction::triggered, [this, index, model]() {
        QString fileName = model->data(index).toString();
        QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();

        DCommit *commitDialog = new DCommit(filePath, nullptr);
        if (commitDialog->exec() == QDialog::Accepted) {
            QString backupFilePath = commitDialog->getBackupFilePath();
            dbmysql.recordSubmission(filePath, backupFilePath);
        }
        commitDialog->deleteLater();
        // if(serverManager->commitToServer(fileName, "upload/"))
        //     dbmysql.recordSubmission(filePath);
    });

    connect(history, &QAction::triggered, [this, index, model]()
    {
        QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();
        QList<QString> filepaths = dbmysql.getRecordSub(filePath);
        this->serverManager->sendfilepaths(filepaths);
    });

    contextMenu.addAction(openAction);
    contextMenu.addAction(deleteAction);
    contextMenu.addAction(newtag);
    contextMenu.addAction(commit);
    contextMenu.addAction(history);

    contextMenu.exec(pos);
}

void TagItemDelegate::addTag(const QAbstractItemModel *model, const QModelIndex &index, DTag &tagDialog) {
    if (tagDialog.exec() == QDialog::Accepted) {
        QStringList tagName = tagDialog.getTagName();
        QString annotation = tagDialog.getAnnotation();
        QDateTime expirationDate = tagDialog.getExpirationDate();

        QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();

        int fileId;

        if (!dbsqlite.getFileId(filePath, fileId)) {
            dbsqlite.addFilePath(filePath, fileId);
        }
        dbsqlite.saveTags(fileId, tagName);
        dbsqlite.saveAnnotation(fileId, annotation);
        dbsqlite.saveExpirationDate(fileId, expirationDate);
    }
}
