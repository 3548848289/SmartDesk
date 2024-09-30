#include "DTag.h"
#include "ui_DTag.h"

DTag::DTag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DTag)
{
    ui->setupUi(this);

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

