#include "ControlWidTXT.h"
#include "ui/ui_ControlWidTXT.h"

ControlWidTXT::ControlWidTXT(QWidget *parent)
    : QWidget(parent), ui(new Ui::ControlWidTXT){
    ui->setupUi(this);
}
