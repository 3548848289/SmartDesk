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
}

void Setting::saveSettings() {
    qDebug() << "完成";
    QSettings settings("MyApp", "MySettings");
    settings.setValue("FontSize", ui->horizontalSlider->value());
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
