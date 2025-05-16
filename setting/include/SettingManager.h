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

    int all_setting_font_size();
    bool all_setting_fenable_tray();

    int file_see_font_size();
    bool file_see_txt();
    bool file_see_csv();
    bool file_see_xlsx();
    bool file_see_img();


    QString tag_schedule_reminder_type();

    QString file_system_file_system_dir();

    int tag_schedule_reminder_time();
    int tag_schedule_interval_time();
    int tag_schedule_show_time();

    void loadHistory();

    void saveHistory();

    int clip_board_hours();

    QString serverconfig_ip();
private:
    SettingManager();
    ~SettingManager();
    QSettings settings;
    QStringList fileHistory;
};

#endif // SETTINGMANAGER_H
