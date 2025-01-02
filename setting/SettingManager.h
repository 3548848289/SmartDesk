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

    bool getEnableTray();

    int getFontSize();

    QString getReminderType();

    int getReminderTime();

    void loadHistory();

    void saveHistory();


private:
    SettingManager();
    ~SettingManager();
    QSettings settings;
    QStringList fileHistory;
};

#endif // SETTINGMANAGER_H
