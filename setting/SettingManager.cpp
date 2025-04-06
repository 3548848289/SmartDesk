#include "include/SettingManager.h"

SettingManager::SettingManager():settings("settings.ini", QSettings::IniFormat) {}

SettingManager::~SettingManager() {}

int SettingManager::all_setting_fontsize() {
    return settings.value("all_setting/font_size", 12).toInt();
}
bool SettingManager::all_setting_fenable_tray() {
    return settings.value("all_setting/fenable_tray", true).toBool();
}


int SettingManager::getFontSize() {
    return settings.value("file_see/font_size", 12).toInt();

}

QString SettingManager::getReminderType() {
    return settings.value("online_doc/reminder_type", "弹窗提醒").toString();
}

QString SettingManager::getFilesystemDir()
{
    return settings.value("file_system/file_system_dir").toString();
}

int SettingManager::getReminderTime() {
    int timeInSeconds = settings.value("online_doc/reminder_time", 1440).toInt();
    return timeInSeconds;
}

int SettingManager::getReminderInterval() {
    int timeInSeconds = settings.value("online_doc/interval_time", 1440).toInt();
    return timeInSeconds;
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

