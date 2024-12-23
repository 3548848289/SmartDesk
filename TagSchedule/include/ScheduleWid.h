#ifndef SCHEDULEWID_H
#define SCHEDULEWID_H

#include <QWidget>
#include <QListWidget>
#include <QTimer>
#include <QString>
#include <QObject>
#include <QStringLiteral>
#include <QDesktopServices>
#include <QUrl>
#include <QListWidgetItem>
#include <QTimer>
#include <QMessageBox>

#include "TagList.h"

#include "../LmsgNotify/notifymanager.h"
// #include "Notify.h"


class DatabaseManager;

namespace Ui {
class ScheduleWid;
}

class ScheduleWid : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleWid(QWidget *parent = nullptr);
    ~ScheduleWid();

signals:
    void fileClicked(const QString &path);

private slots:
    void onItemClicked(QListWidgetItem *item);
    void onSearch(const QString &keyword);

    void on_sortBtn_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    void loadFiles();  // 从数据库加载文件
    void loadTags();  // 从数据库加载标签到ComboBox
    void filterByTag(const QString &tag);  // 基于标签筛选文件

    void startExpirationCheck();
    void checkExpiration();

    QTimer *expirationTimer;
    Ui::ScheduleWid *ui;
    // DBSQlite *dbsqlite;
    NotifyManager *manager;
    dbService& dbservice;

};

#endif // SCHEDULEWid_H
