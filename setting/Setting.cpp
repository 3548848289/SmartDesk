#include "Setting.h"
#include "ui_Setting.h"
#include <QFileDialog>
#include <QCoreApplication>
#include <QSettings>

Setting::Setting(QWidget *parent) : QWidget(parent), ui(new Ui::Setting)
    , settings(QCoreApplication::applicationDirPath() + "/settings.ini", QSettings::IniFormat)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    loadSettings();
}

Setting::~Setting() {
    saveSettings();
    delete ui;
}

void Setting::closeEvent(QCloseEvent *event) {
    delete this;
    event->accept();
}

void Setting::loadSettings() {
    int fontSize = settings.value("FontSize", 12).toInt();
    ui->spinBox->setValue(fontSize);
    bool enableTray = settings.value("enableTray", true).toBool();
    ui->enableTrayCheckBox->setChecked(enableTray);
    QString backupDir = settings.value("BackupDir").toString();
    ui->lineEditBackupDir->setText(backupDir);

    QString reminderType = settings.value("ReminderType", "Popup").toString();
    int reminderIndex = ui->comboBoxReminder->findText(reminderType);
    if (reminderIndex != -1) {
        ui->comboBoxReminder->setCurrentIndex(reminderIndex);
    }

    QTime reminderTime = settings.value("ReminderTime", QTime(0, 1440)).toTime();
    ui->timeEditReminder->setTime(reminderTime);
}


void Setting::saveSettings() {
    settings.setValue("FontSize", ui->spinBox->value());
    settings.setValue("enableTray", ui->enableTrayCheckBox->isChecked());

    QString backupDir = ui->lineEditBackupDir->text();
    if (backupDir.isEmpty()) {
        backupDir = settings.value("BackupDir", QCoreApplication::applicationDirPath() + "/user").toString();
    } else {
        settings.setValue("BackupDir", backupDir);
    }

    settings.setValue("ReminderType", ui->comboBoxReminder->currentText());

    QTime reminderTime = ui->timeEditReminder->time();
    int timeInSeconds = reminderTime.hour() * 3600 + reminderTime.minute() * 60 + reminderTime.second();
    settings.setValue("ReminderTime", timeInSeconds);

    settings.sync();

    qDebug() << "保存设置";
}


void Setting::on_pushButton_clicked() {
    QString selectedDir = QFileDialog::getExistingDirectory(this, "Select Backup Directory", ui->lineEditBackupDir->text());
    if (!selectedDir.isEmpty()) {
        selectedDir.replace("\\", "/");
        ui->lineEditBackupDir->setText(selectedDir);
    }
}



void Setting::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    QTreeWidgetItem *rootItem = item;
    while (rootItem->parent()) {
        rootItem = rootItem->parent();
    }

    int index = rootItem->treeWidget()->indexOfTopLevelItem(rootItem);
    qDebug() << "Root item index: " << index;
    ui->stackedWidget->setCurrentIndex(index);
}

