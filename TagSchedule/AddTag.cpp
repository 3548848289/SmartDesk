#include "./include/AddTag.h"
#include "ui/ui_AddTag.h"

AddTag::AddTag(QWidget *parent) :QDialog(parent),ui(new Ui::AddTag)
{
    ui->setupUi(this);
    QDateTime newDateTime = QDateTime::currentDateTime().addDays(1);
    ui->dateTimeEdit->setDateTime(newDateTime);
}

AddTag::~AddTag()
{
    delete ui;
}

QString AddTag::getTagName() const
{
    return ui->tagsLineEdit->text();
}

QString AddTag::getAnnotation() const
{
    return ui->annotationTextEdit->toPlainText();
}

QDateTime AddTag::getExpirationDate() const
{
    return ui->dateTimeEdit->dateTime();
}

void AddTag::on_saveButton_clicked()
{
    accept();
}

