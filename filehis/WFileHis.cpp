#include "WFileHis.h"
#include "ui_WFileHis.h"

WFileHis::WFileHis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WFileHis)
{
    ui->setupUi(this);
}

WFileHis::~WFileHis()
{
    delete ui;
}
