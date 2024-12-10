#include "Setting.h"
#include "ui_Setting.h"

Setting::Setting(QWidget *parent) :QWidget(parent),ui(new Ui::Setting)
{
    ui->setupUi(this);
    loadSettings();

    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &Setting::onFontSizeChanged);
    connect(ui->lineEdit, &QLineEdit::editingFinished, this, &Setting::onLineEditEditingFinished);
}

Setting::~Setting() {
    saveSettings();
    delete ui;
}

void Setting::loadSettings() {
    QSettings settings("MyApp", "MySettings");
    int fontSize = settings.value("FontSize", 12).toInt();

    ui->horizontalSlider->setRange(8, 72);
    ui->horizontalSlider->setValue(fontSize);
    ui->lineEdit->setText(QString::number(fontSize));
    ui->label->setText(QString("Font Size: %1").arg(fontSize));

    bool enableTray = settings.value("enableTray", true).toBool();  // 默认为启用托盘
    ui->enableTrayCheckBox->setChecked(enableTray);
}

void Setting::saveSettings() {
    QSettings settings("MyApp", "MySettings");
    settings.setValue("FontSize", ui->horizontalSlider->value());

    settings.setValue("enableTray", ui->enableTrayCheckBox->isChecked());
}

void Setting::updateFontSize(int size) {
    ui->lineEdit->setText(QString::number(size));
    ui->label->setText(QString("Font Size: %1").arg(size));
    saveSettings();
}

void Setting::onFontSizeChanged(int value) {
    updateFontSize(value);
}

void Setting::onLineEditEditingFinished() {
    bool ok;
    int size = ui->lineEdit->text().toInt(&ok);
    if (ok) {
        updateFontSize(size);
    }
}

void Setting::on_enableTrayCheckBox_checkStateChanged(const Qt::CheckState &arg1)
{
    saveSettings();

}

