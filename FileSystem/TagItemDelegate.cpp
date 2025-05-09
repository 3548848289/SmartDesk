#include "./include/TagItemDelegate.h"

TagItemDelegate::TagItemDelegate(QObject *parent, ServerManager *serverManager)
    : QStyledItemDelegate(parent), serverManager(serverManager),
    dbservice(dbService::instance("./SmartDesk.db"))
{}



void TagItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
    QString filePath = index.data(QFileSystemModel::FilePathRole).toString();

    if (hasTags(filePath)) {
        QRect iconRect(option.rect.right() - 30, option.rect.top() + 5, 20, 20);
        QIcon tagIcon = QIcon::fromTheme(QIcon::ThemeIcon::MailMessageNew);
        tagIcon.paint(painter, iconRect, Qt::AlignCenter);
    }
    if (dbservice.dbBackup().hasSubmissions(filePath)) {
        QRect submissionIconRect(option.rect.right() - 60, option.rect.top() + 5, 20, 20);
        QIcon submissionIcon = QIcon::fromTheme(QIcon::ThemeIcon::EditCopy);
        submissionIcon.paint(painter, submissionIconRect, Qt::AlignCenter);
    }
}

bool TagItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

        QRect tagIconRect(option.rect.right() - 30, option.rect.top() + 5, 20, 20);
        if (tagIconRect.contains(mouseEvent->pos())) {
            isButtonClicked = true;
            emit tagbutClicked(index);

            QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();
            TagDetail *tagDetail = new TagDetail(nullptr, filePath);
            tagDetail->show();

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
    QAction *commit = new QAction("文件备份", &contextMenu);
    QAction *history = new QAction("提交历史", &contextMenu);
    QAction *copyAction = new QAction("复制路径", &contextMenu);

    connect(newtag, &QAction::triggered, [this, model, index]() { onNewTagTriggered(model, index); });
    connect(openAction, &QAction::triggered, [this, model, index]() { onOpenFileTriggered(model, index); });
    connect(deleteAction, &QAction::triggered, [this, model, index]() { onDeleteFileTriggered(model, index); });
    connect(commit, &QAction::triggered, [this, model, index]() { onCommitTriggered(model, index); });
    connect(history, &QAction::triggered, [this, model, index]() { onHistoryTriggered(model, index); });
    connect(copyAction, &QAction::triggered, [this, model, index]() { onCopyPathTriggered(model, index); });

    contextMenu.addAction(openAction);
    contextMenu.addAction(deleteAction);
    contextMenu.addAction(newtag);
    contextMenu.addAction(commit);
    contextMenu.addAction(history);
    contextMenu.addAction(copyAction);
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
    QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();
    QMessageBox msgBox;
    msgBox.setWindowTitle("删除文件");
    msgBox.setText("你确定要删除这个文件吗?");
    msgBox.setWindowIcon(QIcon::fromTheme("utilities-system-monitor"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes) {
        QFile file(filePath);
        if (file.remove()) {
            model->removeRow(index.row());
        } else {
            qWarning() << "删除文件失败:" << filePath << "错误:" << file.errorString();
        }
        emit deleteFileRequested(filePath);
    }
}

void TagItemDelegate::onCommitTriggered(QAbstractItemModel *model, const QModelIndex &index) {
    QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();
    FileBackupWid *commitDialog = new FileBackupWid(filePath, nullptr);
    if (commitDialog->exec() == QDialog::Accepted) {
        QString backupFilePath = commitDialog->getBackupFilePath();
        dbservice.dbBackup().recordSubmission(filePath, backupFilePath);
    }
    commitDialog->deleteLater();
}

void TagItemDelegate::onHistoryTriggered(QAbstractItemModel *model, const QModelIndex &index) {
    QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();
    this->serverManager->sendfilepath(filePath);
}

void TagItemDelegate::addTag(const QAbstractItemModel *model, const QModelIndex &index, AddTag &tagDialog) {
    if (tagDialog.exec() == QDialog::Accepted) {
        QString tagName = tagDialog.getTagName();
        qDebug() << tagName;
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

void TagItemDelegate::onCopyPathTriggered(QAbstractItemModel *model, const QModelIndex &index)
{
    if (!index.isValid()) {
        return;
    }
    // 假设 model 是 QFileSystemModel
    QFileSystemModel *fileSystemModel = qobject_cast<QFileSystemModel*>(model);
    if (fileSystemModel) {
        QString filePath = fileSystemModel->filePath(index);  // 获取文件路径
        if (!filePath.isEmpty()) {
            QClipboard *clipboard = QGuiApplication::clipboard();
            clipboard->setText(filePath);  // 将文件路径复制到剪贴板
        }
    }
}
