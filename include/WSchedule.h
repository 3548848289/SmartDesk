#ifndef WSCHEDULE_H
#define WSCHEDULE_H

#include <QWidget>
#include <QStandardItemModel>
#include "../manager/DatabaseManager.h"

class DatabaseManager;

namespace Ui {
class WSchedule;
}

class WSchedule : public QWidget
{
    Q_OBJECT

public:
    explicit WSchedule(DatabaseManager *dbManager, QWidget *parent = nullptr);
    ~WSchedule();

signals:
    void fileClicked(const QString &filePath);

private slots:
    void onFileClicked(const QModelIndex &index);  // 文件点击事件处理
    void onTagSelected(const QString &tag);  // 标签筛选事件处理
    void onSearchTextChanged(const QString &keyword);  // 关键词搜索事件处理
    void sortByExpirationDate(); // 新增排序功能

private:
    void loadFilesFromDatabase();  // 从数据库加载文件
    void loadTagsIntoComboBox();  // 从数据库加载标签到ComboBox
    void filterFilesByTag(const QString &tag);  // 基于标签筛选文件
    void filterFilesByKeyword(const QString &keyword);  // 基于关键词筛选文件

    Ui::WSchedule *ui;
    DatabaseManager *dbManager;
    QStandardItemModel *model;  // 用于 listView 的模型
};

#endif // WSCHEDULE_H
