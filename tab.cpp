#include "tab.h"
#include "ui_tab.h"



Tab::Tab(QWidget *parent) :QWidget(parent), ui(new Ui::Tab)
{
    ui->setupUi(this);
}

void Tab::TabSetText(const QString& text)
{
    if (ui->textEdit)
        ui->textEdit->setPlainText(text);
    else
        qDebug() << "ui->textEdit is null in TabSetText";
}

Tab::~Tab()
{

}

QString Tab::TabGetText()
{
    if (ui->textEdit)
        return ui->textEdit->toPlainText();
    qDebug() << "ui->textEdit is null in TabGetText";
    return QString();
}
