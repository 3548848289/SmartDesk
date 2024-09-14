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


void WidgetFunctional::on_pushButton_1_clicked() {
    emit showRU();
}

void WidgetFunctional::on_pushButton_2_clicked() {
    emit showRD();
}
