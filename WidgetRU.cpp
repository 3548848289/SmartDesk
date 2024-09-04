#include "WidgetRU.h"
#include "ui_WidgetRU.h"

WidgetRU::WidgetRU(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetRU)
{
    ui->setupUi(this);
}

WidgetRU::~WidgetRU()
{
    delete ui;
}
