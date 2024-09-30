#include "DPull.h"
#include "ui_DPull.h"

DPull::DPull(QString fileName, ServerManager* serverManager, QWidget *parent)
    :QDialog(parent), ui(new Ui::DPull), fileName(fileName), serverManager(serverManager)
{
    ui->setupUi(this);
    ui->lineEdit->setText(fileName);
}

DPull::~DPull()
{
    delete ui;
}

void DPull::on_fastDlBtn_clicked()
{
    serverManager->downloadFile(fileName);
}


void DPull::on_dlBtn_clicked()
{

}

