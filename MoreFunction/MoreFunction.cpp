#include "MoreFunction.h"
#include "ui_MoreFunction.h"

MoreFunction::MoreFunction(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MoreFunction)
{
    ui->setupUi(this);
}

MoreFunction::~MoreFunction()
{
    delete ui;
}
