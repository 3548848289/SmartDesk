#include "include/Setting.h"
#include "ui/ui_Setting.h"
#include <QFileDialog>
#include <QCoreApplication>
#include <QSettings>

Setting::Setting(QWidget *parent) : QWidget(parent), ui(new Ui::Setting)
    , settings("settings.ini", QSettings::IniFormat)  // 使用资源路径
{

    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->treeWidget->setHeaderHidden(true);

    ui->tag_schedule_timeEdit1->setDisplayFormat("HH:mm");
    ui->tag_schedule_timeEdit2->setDisplayFormat("HH:mm");
    ui->tag_schedule_timeEdit3->setDisplayFormat("HH:mm");

    if (settings.status() == QSettings::NoError) {
        loadSettings();
    } else {
        qDebug() << "Settings file status: " << settings.status();
    }
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
    ui->file_see_checkBox1->setChecked(settings.value("file_see/txt", true).toBool());
    ui->file_see_checkBox2->setChecked(settings.value("file_see/csv", true).toBool());
    ui->file_see_checkBox3->setChecked(settings.value("file_see/xlsx", true).toBool());
    ui->file_see_checkBox4->setChecked(settings.value("file_see/img", true).toBool());


    ui->file_backup_lineEdit->setText(settings.value("file_backup/backup_dir").toString());

    int reminderIndex = ui->tag_schedule_comboBox->findText(
        settings.value("tag_schedule/reminder_type", "Popup").toString());
    if (reminderIndex != -1)
        ui->tag_schedule_comboBox->setCurrentIndex(reminderIndex);

    QTime time = QTime(0, 0).addSecs(settings.value("tag_schedule/reminder_time", 0).toInt());
    ui->tag_schedule_timeEdit1->setTime(time);
    QTime interval = QTime(0, 0).addSecs(settings.value("tag_schedule/interval_time", 0).toInt());
    ui->tag_schedule_timeEdit2->setTime(interval);
    QTime showtime = QTime(0, 0).addSecs(settings.value("tag_schedule/show_time", 0).toInt());
    ui->tag_schedule_timeEdit3->setTime(showtime);

    ui->email_service_lineEdit_1->setText(settings.value("EmailConfig/host").toString());
    ui->email_service_lineEdit_2->setText(settings.value("EmailConfig/username").toString());
    ui->email_service_lineEdit_3->setText(settings.value("EmailConfig/password").toString());
    ui->email_service_lineEdit_4->setText(settings.value("EmailConfig/port").toString());
    ui->email_service_lineEdit_5->setText(settings.value("EmailConfig/sender").toString());
    ui->email_service_lineEdit_6->setText(settings.value("EmailConfig/received").toString());

    ui->clip_board_spinBox->setValue(settings.value("clip_board/hours", 24).toInt());
    ui->server_config_lineEdit->setText(settings.value("ServerConfig/IP", "127.0.0.1").toString());
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
    settings.setValue("file_see/txt", ui->file_see_checkBox1->isChecked());
    settings.setValue("file_see/csv", ui->file_see_checkBox2->isChecked());
    settings.setValue("file_see/xlsx", ui->file_see_checkBox3->isChecked());
    settings.setValue("file_see/img", ui->file_see_checkBox4->isChecked());

    QString backupDir = ui->file_backup_lineEdit->text();
    if (backupDir.isEmpty())
        backupDir = settings.value("file_backup/backup_dir", QCoreApplication::applicationDirPath() + "/user").toString();
    else
        settings.setValue("file_backup/backup_dir", backupDir);

    settings.setValue("tag_schedule/reminder_type", ui->tag_schedule_comboBox->currentText());
    QTime reminderTime = ui->tag_schedule_timeEdit1->time();
    int timeInSeconds = reminderTime.hour() * 3600 + reminderTime.minute() * 60 + reminderTime.second();
    settings.setValue("tag_schedule/reminder_time", timeInSeconds);

    QTime Interval = ui->tag_schedule_timeEdit2->time();
    int IntervalInSeconds = Interval.hour() * 3600 + Interval.minute() * 60 + Interval.second();
    settings.setValue("tag_schedule/interval_time", IntervalInSeconds);

    QTime showTime = ui->tag_schedule_timeEdit3->time();
    int showTimeInSeconds = showTime.hour() * 3600 + showTime.minute() * 60 + showTime.second();
    settings.setValue("tag_schedule/show_time", showTimeInSeconds);

    settings.setValue("EmailConfig/host", ui->email_service_lineEdit_1->text());
    settings.setValue("EmailConfig/username", ui->email_service_lineEdit_2->text());
    settings.setValue("EmailConfig/password", ui->email_service_lineEdit_3->text());
    settings.setValue("EmailConfig/port", ui->email_service_lineEdit_4->text());
    settings.setValue("EmailConfig/sender", ui->email_service_lineEdit_5->text());
    settings.setValue("EmailConfig/received", ui->email_service_lineEdit_6->text());

    settings.setValue("clip_board/hours", ui->clip_board_spinBox->text());

    settings.setValue("ServerConfig/IP", ui->server_config_lineEdit->text());
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

