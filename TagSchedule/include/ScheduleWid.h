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
#include "../../Setting/include/SettingManager.h"
#include "../LmsgNotify/notifymanager.h"
#include "../../EmailService/SendEmail.h"

class DatabaseManager;
namespace Ui { class ScheduleWid; }
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
    void on_comboBox_currentIndexChanged(int index);
    void on_sortComboBox_currentIndexChanged(int index);

private:
    void loadFiles();
    void loadTags();
    void filterByTag(const QString &tag);

    void startExpirationCheck();
    void checkExpiration();

    QTimer *expirationTimer;
    Ui::ScheduleWid *ui;
    NotifyManager *manager;
    SendEmail * sendemail;
    dbService& dbservice;

};

#endif // SCHEDULEWid_H
