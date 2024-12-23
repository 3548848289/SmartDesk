#include "FileContextMenu.h"


FileContextMenu::FileContextMenu(ServerManager *serverManager, dbService &dbservice, QObject *parent)
    : QObject(parent), serverManager(serverManager), dbservice(dbservice) {}

void FileContextMenu::showContextMenu(const QPoint &pos, const QModelIndex &index, QAbstractItemModel *model) {
    QMenu contextMenu;

    QAction *openAction = new QAction("打开文件", &contextMenu);
    QAction *deleteAction = new QAction("删除文件", &contextMenu);
    QAction *newTagAction = new QAction("新建标签", &contextMenu);
    QAction *commitAction = new QAction("提交远程", &contextMenu);
    QAction *historyAction = new QAction("提交历史", &contextMenu);

    connect(newTagAction, &QAction::triggered, [this, model, index]() { onNewTagTriggered(model, index); });
    connect(openAction, &QAction::triggered, [this, model, index]() { onOpenFileTriggered(model, index); });
    connect(deleteAction, &QAction::triggered, [this, model, index]() { onDeleteFileTriggered(model, index); });
    connect(commitAction, &QAction::triggered, [this, model, index]() { onCommitTriggered(model, index); });
    connect(historyAction, &QAction::triggered, [this, model, index]() { onHistoryTriggered(model, index); });

    contextMenu.addAction(openAction);
    contextMenu.addAction(deleteAction);
    contextMenu.addAction(newTagAction);
    contextMenu.addAction(commitAction);
    contextMenu.addAction(historyAction);

    contextMenu.exec(pos);
}

void FileContextMenu::onNewTagTriggered(QAbstractItemModel *model, const QModelIndex &index) {
    // 触发新标签的处理
    emit onFilesListUpdated(QStringList() << "new tag triggered");
}

void FileContextMenu::onOpenFileTriggered(QAbstractItemModel *model, const QModelIndex &index) {
    QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();
    emit openFileRequested(filePath);
}

void FileContextMenu::onDeleteFileTriggered(QAbstractItemModel *model, const QModelIndex &index) {
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

void FileContextMenu::onCommitTriggered(QAbstractItemModel *model, const QModelIndex &index) {
    QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();
    // 提交远程处理
    emit onFilesListUpdated(QStringList() << "commit triggered for " << filePath);
}

void FileContextMenu::onHistoryTriggered(QAbstractItemModel *model, const QModelIndex &index) {
    QString filePath = model->data(index, QFileSystemModel::FilePathRole).toString();
    // 提交历史处理
    emit onFilesListUpdated(QStringList() << "history triggered for " << filePath);
}
