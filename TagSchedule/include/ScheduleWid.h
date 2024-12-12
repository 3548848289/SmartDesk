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

#include "../../manager/include/dbService.h"
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
    void onItemClicked(QListWidgetItem *item);  // 文件点击事件
    void onTagChanged(const QString &tag);  // 标签筛选事件
    void onSearch(const QString &keyword);  // 关键词搜索事件
    void sortByExpDate(); // 新增排序功能

    void onSortClicked();

    void on_pushButton_clicked();

private:
    QString getExpInfo(const QString &path, const QDateTime &dateTime);
    void loadFiles();  // 从数据库加载文件
    void loadTags();  // 从数据库加载标签到ComboBox
    void filterByTag(const QString &tag);  // 基于标签筛选文件
    void filterByKeyword(const QString &keyword);  // 基于关键词筛选文件

    void startExpirationCheck();
    void checkExpiration();

    QTimer *expirationTimer;
    Ui::ScheduleWid *ui;
    // DBSQlite *dbsqlite;
    NotifyManager *manager;
    dbService& dbservice;

};

#endif // SCHEDULEWid_H
