#include "include/AppHelp.h"
#include "ui/ui_AppHelp.h"

AppHelp::AppHelp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AppHelp)
{
    ui->setupUi(this);
    QLabel * label = new QLabel(this);
    label->setText("帮助");
}

AppHelp::~AppHelp()
{
    delete ui;
}
