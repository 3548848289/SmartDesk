#ifndef WSCHEDULE_H
#define WSCHEDULE_H

#include <QWidget>
#include <QListWidget>
#include <QTimer>
#include "../manager/include/DBSQlite.h"

class DatabaseManager;

namespace Ui {
class WSchedule;
}

class WSchedule : public QWidget
{
    Q_OBJECT

public:
    explicit WSchedule(DBSQlite *db, QWidget *parent = nullptr);
    ~WSchedule();

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
    Ui::WSchedule *ui;
    DBSQlite *db;
};

#endif // WSCHEDULE_H
