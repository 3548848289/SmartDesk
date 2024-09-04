#include "RecentFilesManager.h"
#include <QMenu>
#include <QAction>
#include <QCursor>

RecentFilesManager::RecentFilesManager(QObject *parent) : QObject(parent) {
    loadHistory();
}

RecentFilesManager::~RecentFilesManager() {
    saveHistory();
}

void RecentFilesManager::addFile(const QString &filePath) {
    if (fileHistory.contains(filePath)) {
        fileHistory.removeAll(filePath);
    }
    fileHistory.prepend(filePath);
    if (fileHistory.size() > maxRecentFiles) {
        fileHistory.removeLast();
    }
    saveHistory();
}

void RecentFilesManager::loadHistory() {
    QSettings settings("MyCompany", "MyApp");
    int size = settings.beginReadArray("fileHistory");
    fileHistory.clear();
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        fileHistory.append(settings.value("path").toString());
    }
    settings.endArray();
}

void RecentFilesManager::saveHistory() {
    QSettings settings("MyCompany", "MyApp");
    settings.beginWriteArray("fileHistory");
    for (int i = 0; i < fileHistory.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("path", fileHistory[i]);
    }
    settings.endArray();
}

void RecentFilesManager::populateRecentFilesMenu(QMenu *menu) {
    menu->clear();
    for (const QString &filePath : qAsConst(fileHistory)) {
        QAction *action = new QAction(filePath, menu);
        connect(action, &QAction::triggered, this, [this, filePath]() {
            emit fileOpened(filePath);
        });
        menu->addAction(action);
    }
}
