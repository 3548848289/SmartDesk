#include "SettingManager.h"

SettingManager::SettingManager():settings("settings.ini", QSettings::IniFormat) {}

SettingManager::~SettingManager() {}


bool SettingManager::getEnableTray() {
    return settings.value("enableTray", true).toBool();
}

int SettingManager::getFontSize() {
    return settings.value("FontSize", 12).toInt();

}

QString SettingManager::getReminderType() {
    return settings.value("ReminderType", "Popup").toString();  // 默认提醒方式为 "Popup"
}

int SettingManager::getReminderTime() {
    int timeInSeconds = settings.value("ReminderTime", 600).toInt();  // 默认 10 分钟（600秒）
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

