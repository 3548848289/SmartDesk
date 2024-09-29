#include "DCommit.h"
#include "../ui/ui_DCommit.h"

DCommit::DCommit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DCommit)
{
    ui->setupUi(this);
}

DCommit::~DCommit()
{
    delete ui;
}
