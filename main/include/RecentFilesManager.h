#ifndef RECENTFILESMANAGER_H
#define RECENTFILESMANAGER_H

#include <QObject>
#include <QStringList>
#include <QSettings>
#include <QAction>
#include <QMenu>
#include "../../Setting/SettingManager.h"

class RecentFilesManager : public QObject
{
    Q_OBJECT

public:
    explicit RecentFilesManager(QObject *parent = nullptr);
    ~RecentFilesManager();

    void addFile(const QString &filePath);
    void loadHistory();
    void saveHistory();
    void populateRecentFilesMenu(QMenu *menu);

signals:
    void fileOpened(const QString &filePath);

private:
    QStringList fileHistory;
    const int maxRecentFiles = 10; // Maximum number of recent files to keep
};

#endif // RECENTFILESMANAGER_H
