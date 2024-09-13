#include "WidgetFunctional.h"
#include "ui_WidgetFunctional.h"

WidgetFunctional::WidgetFunctional(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetFunctional)
{
    ui->setupUi(this);
}

WidgetFunctional::~WidgetFunctional()
{
    delete ui;
}
