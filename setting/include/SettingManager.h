#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#include<QSettings>

class SettingManager
{
public:
    // 获取单例实例的静态方法
    static SettingManager& Instance()
    {
        static SettingManager instance;
        return instance;
    }

    // 禁止拷贝构造和赋值
    SettingManager(const SettingManager&) = delete;
    SettingManager& operator=(const SettingManager&) = delete;

    int all_setting_fontsize();
    bool all_setting_fenable_tray();

    int getFontSize();

    QString getReminderType();

    QString getFilesystemDir();

    int getReminderTime();
    int getReminderInterval();

    void loadHistory();

    void saveHistory();


private:
    SettingManager();
    ~SettingManager();
    QSettings settings;
    QStringList fileHistory;
};

#endif // SETTINGMANAGER_H
