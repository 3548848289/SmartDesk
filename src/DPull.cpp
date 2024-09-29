#include "DPull.h"
#include "../ui/ui_DPull.h"

DPull::DPull(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DPull)
{
    ui->setupUi(this);
}

DPull::~DPull()
{
    delete ui;
}
