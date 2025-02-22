#include "include/FindDialog.h"
#include "ui/ui_FindDialog.h"

FindDialog::FindDialog(QWidget *parent): QDialog(parent), ui(new Ui::FindDialog)
{
    ui->setupUi(this);
    ui->label->setBuddy(ui->lineEdit);
    ui->findButton->setDefault(true);
    ui->findButton->setEnabled(false);
}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::on_lineEdit_textChanged(const QString &arg1)
{
    ui->findButton->setEnabled(!arg1.isEmpty());
}


void FindDialog::on_findButton_clicked()
{
    QString text = ui->lineEdit->text();
    Qt::CaseSensitivity cs =
        ui->caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    emit findNext(text, cs);
}


void FindDialog::on_findAllButton_clicked()
{
    QString text = ui->lineEdit->text();
    Qt::CaseSensitivity cs =
        ui->caseCheckBox->isChecked() ? Qt::CaseSensitive
                                      : Qt::CaseInsensitive;
    emit findAll(text, cs);
}

