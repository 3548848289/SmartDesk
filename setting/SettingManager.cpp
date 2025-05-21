#include "include/SettingManager.h"

SettingManager::SettingManager():settings("settings.ini", QSettings::IniFormat) {}

SettingManager::~SettingManager() {}

int SettingManager::all_setting_font_size() {
    return settings.value("all_setting/font_size", 12).toInt();
}
bool SettingManager::all_setting_fenable_tray() {
    return settings.value("all_setting/fenableray", true).toBool();
}


int SettingManager::file_see_font_size() {
    return settings.value("file_see/font_size", 12).toInt();

}

bool SettingManager::file_see_txt()
{
    return settings.value("file_see/txt", true).toBool();
}

bool SettingManager::file_see_csv()
{
    return settings.value("file_see/csv", true).toBool();
}

bool SettingManager::file_see_xlsx()
{
    return settings.value("file_see/slsx", true).toBool();
}

bool SettingManager::file_see_img()
{
    return settings.value("file_see/img", true).toBool();
}

QString SettingManager::file_backup_IP()
{
    return settings.value("file_backup/IP", "127.0.0.1").toString();
}


QString SettingManager::tag_schedule_reminder_type() {
    return settings.value("tag_schedule/reminder_type", "弹窗提醒").toString();
}

QString SettingManager::file_system_file_system_dir()
{
    return settings.value("file_system/file_system_dir").toString();
}

int SettingManager::tag_schedule_reminder_time() {
    int timeInSeconds = settings.value("tag_schedule/reminder_time", 1440).toInt();
    return timeInSeconds;
}

int SettingManager::tag_schedule_interval_time() {
    int timeInSeconds = settings.value("tag_schedule/interval_time", 1440).toInt();
    return timeInSeconds;
}

int SettingManager::tag_schedule_show_time() {
    int timeInSeconds = settings.value("tag_schedule/show_time", 1440).toInt();
    return timeInSeconds;
}

int SettingManager::clip_board_hours() {
    int hours = settings.value("clip_board/hours", 24).toInt();
    return hours;
}

QString SettingManager::serverconfig_ip1()
{
    return settings.value("ServerConfig/IP1", "43.139.86.56:5002").toString();
}

QString SettingManager::serverconfig_ip2()
{
    return settings.value("ServerConfig/IP2", "43.139.86.56:5000").toString();
}
QString SettingManager::serverconfig_ip3()
{
    return settings.value("ServerConfig/IP3", "43.139.86.56:9200").toString();
}
QString SettingManager::serverconfig_ip4()
{
    return settings.value("ServerConfig/IP4", "43.139.86.56:5001").toString();
}

void SettingManager::loadHistory()
{
    int size = settings.beginReadArray("fileHistory");
    fileHistory.clear();
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        fileHistory.append(settings.value("path").toString());
    }
    settings.endArray();
}

void SettingManager::saveHistory()
{
    settings.beginWriteArray("fileHistory");
    for (int i = 0; i < fileHistory.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("path", fileHistory[i]);
    }
    settings.endArray();
}

