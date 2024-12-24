#include "./include/TagItemDelegate.h"

TagItemDelegate::TagItemDelegate(QObject *parent, ServerManager *serverManager)
    : QStyledItemDelegate(parent), serverManager(serverManager),
    dbservice(dbService::instance("../SmartDesk.db"))
{}



void TagItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
    QString filePath = index.data(QFileSystemModel::FilePathRole).toString();

    if (hasTags(filePath)) {
        QRect iconRect(option.rect.right() - 30, option.rect.top() + 5, 20, 20);
        QIcon tagIcon(":/usedimage/edittag.svg");
        tagIcon.paint(painter, iconRect, Qt::AlignCenter);
    }
    if (dbservice.dbBackup().hasSubmissions(filePath)) {
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
            AddTag tagDialog;
            addTag(model, index, tagDialog);
            isButtonClicked = true;
            emit tagbutClicked(index);
            return true;
        }

        QRect submissionButtonRect(option.rect.right() - 60, option.rect.top() + 5, 20, 20);
        if (submissionButtonRect.contains(mouseEvent->pos())) {
            onHistoryTriggered(model, index);
            isButtonClicked = true;
            // this->serverManager->getFilesInDirectory(index, model);
            emit subbutClicked(index);

            return true;
        }
    }

    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::RightButton && option.rect.contains(mouseEvent->pos())) {
            showContextMenu(mouseEvent->globalPosition().toPoint(), index, model);
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

    bool hasTags = dbservice.dbTags().hasTagsForFile(filePath);
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

    connect(newtag, &QAction::triggered, [this, model, index]() { onNewTagTriggered(model, index); });
    connect(openAction, &QAction::triggered, [this, model, index]() { onOpenFileTriggered(model, index); });
    connect(deleteAction, &QAction::triggered, [this, model, index]() { onDeleteFileTriggered(model, index); });
    connect(commit, &QAction::triggered, [this, model, index]() { onCommitTriggered(model, index); });
    connect(history, &QAction::triggered, [this, model, index]() { onHistoryTriggered(model, index); });

    contextMenu.addAction(openAction);
    contextMenu.addAction(deleteAction);
    contextMenu.addAction(newtag);
    contextMenu.addAction(commit);
    contextMenu.addAction(history);

    contextMenu.exec(pos);
}

void TagItemDelegate::onNewTagTriggered(QAbstractItemModel *model, const QModelIndex &index) {
    AddTag tagDialog;
    addTag(model, index, tagDialog);
}

void TagItemDelegate::onOpenFileTriggered(QAbstractItemModel *model, const QModelIndex &index) {
    QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();
    emit openFileRequested(filePath);
}

void TagItemDelegate::onDeleteFileTriggered(QAbstractItemModel *model, const QModelIndex &index) {
    qDebug() << "TagItemDelegate::onDeleteFileTriggered 文件删除功能隐藏了";
    return;

    QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();
    QFile file(filePath);
    if (file.remove()) {
        qDebug() << "文件已删除:" << filePath;
        model->removeRow(index.row());
    } else {
        qWarning() << "删除文件失败:" << filePath << "错误:" << file.errorString();
    }
    emit deleteFileRequested(filePath);
}

void TagItemDelegate::onCommitTriggered(QAbstractItemModel *model, const QModelIndex &index) {
    QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();
    FileBackup *commitDialog = new FileBackup(filePath, nullptr);
    if (commitDialog->exec() == QDialog::Accepted) {
        QString backupFilePath = commitDialog->getBackupFilePath();
        dbservice.dbBackup().recordSubmission(filePath, backupFilePath);
    }
    commitDialog->deleteLater();
}

void TagItemDelegate::onHistoryTriggered(QAbstractItemModel *model, const QModelIndex &index) {
    QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();
    QList<QString> filepaths = dbservice.dbBackup().getRecordSub(filePath);
    this->serverManager->sendfilepaths(filepaths);
}

void TagItemDelegate::addTag(const QAbstractItemModel *model, const QModelIndex &index, AddTag &tagDialog) {
    if (tagDialog.exec() == QDialog::Accepted) {
        QString tagName = tagDialog.getTagName();
        QString annotation = tagDialog.getAnnotation();
        QDateTime expirationDate = tagDialog.getExpirationDate();

        QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();

        int fileId;

        if (!dbservice.dbTags().getFileId(filePath, fileId)) {
            dbservice.dbTags().addFilePath(filePath, fileId);
            dbservice.dbTags().saveTags(fileId, tagName);
            dbservice.dbTags().saveAnnotation(fileId, annotation);
            dbservice.dbTags().saveExpirationDate(fileId, expirationDate);

        }
        else {
            FilePathInfo fileInfo;
            fileInfo.filePath = filePath;
            fileInfo.tagName = tagName;
            fileInfo.expirationDate = expirationDate;
            fileInfo.annotation = annotation;
            dbservice.dbTags().updateFileInfo(fileInfo);
        }

        emit TagUpdated();
    }
}
