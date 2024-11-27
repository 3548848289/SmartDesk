#include "./include/DTag.h"
#include "ui/ui_DTag.h"

DTag::DTag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DTag)
{
    ui->setupUi(this);
    QDateTime newDateTime = QDateTime::currentDateTime().addDays(1);
    ui->dateTimeEdit->setDateTime(newDateTime);
}

DTag::~DTag()
{
    delete ui;
}

QStringList DTag::getTagName() const
{
    return ui->tagsLineEdit->text().split(", ");
}

QString DTag::getAnnotation() const
{
    return ui->annotationTextEdit->toPlainText();
}

QDateTime DTag::getExpirationDate() const
{
    return ui->dateTimeEdit->dateTime();
}

void DTag::on_saveButton_clicked()
{
    accept();
}

