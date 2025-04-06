#include "include/Setting.h"
#include "ui/ui_Setting.h"
#include <QFileDialog>
#include <QCoreApplication>
#include <QSettings>

Setting::Setting(QWidget *parent) : QWidget(parent), ui(new Ui::Setting)
    , settings(QCoreApplication::applicationDirPath() + "/settings.ini", QSettings::IniFormat)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->online_doc_timeEdit_1->setDisplayFormat("HH:mm");
    ui->online_doc_timeEdit_2->setDisplayFormat("HH:mm");
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
    ui->all_setting_spinBox->setValue(settings.value("all_setting/font_size", 12).toInt());
    ui->all_setting_checkBox->setChecked(settings.value("all_setting/fenableray", true).toBool());
    ui->file_system_lineEdit->setText(settings.value("file_system/file_system_dir").toString());
    ui->file_see_spinBox->setValue(settings.value("file_see/font_size", 12).toInt());
    ui->file_backup_lineEdit->setText(settings.value("file_backup/backup_dir").toString());

    int reminderIndex = ui->online_doc_comboBox->findText(
        settings.value("online_doc/reminder_type", "Popup").toString());
    if (reminderIndex != -1)
        ui->online_doc_comboBox->setCurrentIndex(reminderIndex);
    QTime time = QTime(0, 0).addSecs(settings.value("online_doc/reminder_time", 0).toInt());
    ui->online_doc_timeEdit_1->setTime(time);
    QTime interval = QTime(0, 0).addSecs(settings.value("online_doc/interval_time", 0).toInt());
    ui->online_doc_timeEdit_2->setTime(interval);

    ui->email_service_lineEdit_1->setText(settings.value("EmailConfig/host").toString());
    ui->email_service_lineEdit_2->setText(settings.value("EmailConfig/username").toString());
    ui->email_service_lineEdit_3->setText(settings.value("EmailConfig/password").toString());
    ui->email_service_lineEdit_4->setText(settings.value("EmailConfig/port").toString());
    ui->email_service_lineEdit_5->setText(settings.value("EmailConfig/sender").toString());
    ui->email_service_lineEdit_6->setText(settings.value("EmailConfig/received").toString());


}

void Setting::saveSettings() {
    settings.setValue("all_setting/font_size", ui->all_setting_spinBox->value());
    settings.setValue("all_setting/fenableray", ui->all_setting_checkBox->isChecked());

    QString filesystemDir = ui->file_system_lineEdit->text();
    if (filesystemDir.isEmpty())
        filesystemDir = settings.value("file_system/file_system_dir", QStandardPaths::writableLocation(QStandardPaths::HomeLocation)).toString();
    else
        settings.setValue("file_system/file_system_dir", filesystemDir);

    settings.setValue("file_see/font_size", ui->file_see_spinBox->value());

    QString backupDir = ui->file_backup_lineEdit->text();
    if (backupDir.isEmpty())
        backupDir = settings.value("file_backup/backup_dir", QCoreApplication::applicationDirPath() + "/user").toString();
    else
        settings.setValue("file_backup/backup_dir", backupDir);


    settings.setValue("online_doc/reminder_type", ui->online_doc_comboBox->currentText());
    QTime reminderTime = ui->online_doc_timeEdit_1->time();
    int timeInSeconds = reminderTime.hour() * 3600 + reminderTime.minute() * 60 + reminderTime.second();
    settings.setValue("online_doc/reminder_time", timeInSeconds);
    QTime Interval = ui->online_doc_timeEdit_2->time();
    int IntervalInSeconds = Interval.hour() * 3600 + Interval.minute() * 60 + Interval.second();
    settings.setValue("online_doc/interval_time", IntervalInSeconds);

    settings.setValue("EmailConfig/host", ui->email_service_lineEdit_1->text());
    settings.setValue("EmailConfig/username", ui->email_service_lineEdit_2->text());
    settings.setValue("EmailConfig/password", ui->email_service_lineEdit_3->text());
    settings.setValue("EmailConfig/port", ui->email_service_lineEdit_4->text());
    settings.setValue("EmailConfig/sender", ui->email_service_lineEdit_5->text());
    settings.setValue("EmailConfig/received", ui->email_service_lineEdit_6->text());

    settings.sync();
}


void Setting::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    QTreeWidgetItem *rootItem = item;
    while (rootItem->parent()) {
        rootItem = rootItem->parent();
    }
    int index = rootItem->treeWidget()->indexOfTopLevelItem(rootItem);
    ui->stackedWidget->setCurrentIndex(index);
}





void Setting::on_file_system_Btn_clicked()
{
    QString selectedDir = QFileDialog::getExistingDirectory(this, "Select Filesystem Directory", ui->file_system_lineEdit->text());
    if (!selectedDir.isEmpty()) {
        selectedDir.replace("\\", "/");
        ui->file_system_lineEdit->setText(selectedDir);
    }
}


void Setting::on_file_backup_Btn_clicked()
{
    QString selectedDir = QFileDialog::getExistingDirectory(this, "Select Backup Directory", ui->file_backup_lineEdit->text());
    if (!selectedDir.isEmpty()) {
        selectedDir.replace("\\", "/");
        ui->file_backup_lineEdit->setText(selectedDir);
    }
}

