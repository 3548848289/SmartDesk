#include "WidgetFunctional.h"
#include "../ui/ui_WidgetFunctional.h"

WidgetFunctional::WidgetFunctional(QWidget *parent) :QWidget(parent),ui(new Ui::WidgetFunctional)
{
    ui->setupUi(this);
    btnGroup=new QButtonGroup;

    for (int i = 1; i <= 5; ++i) {
        QPushButton *button = findChild<QPushButton*>(QString("pushButton_%1").arg(i));
        if (button) {
            btnGroup->addButton(button);
            button->setCheckable(true);

            connect(button, &QPushButton::clicked, this, [=]() {
                foreach(QAbstractButton *btn, btnGroup->buttons()) {
                    btn->setChecked(btn->objectName() == QString("pushButton_%1").arg(i));
                }
            });
        }
    }

    this->setStyleSheet("QPushButton#pushButton_1, QPushButton#pushButton_2,"
                        "QPushButton#pushButton_3, QPushButton#pushButton_4,"
                        "QPushButton#pushButton_5"
                        "{background:transparent;border:none;color:#000000;}"

                        "QPushButton#pushButton_1:checked,QPushButton#pushButton_2:checked,"
                        "QPushButton#pushButton_3:checked,QPushButton#pushButton_4:checked,"
                        "QPushButton#pushButton_5:checked "
                        "{background:transparent;border:none;   border-bottom:3px solid #3598db;color:#3598db;}"

                        "QPushButton#pushButton_1:hover,QPushButton#pushButton_2:hover,"
                        "QPushButton#pushButton_3:hover,QPushButton#pushButton_4:hover,"
                        "QPushButton#pushButton_5:hover,"
                        "{background:transparent;border:none;   border-bottom:3px solid #7598db;color:#7598db;}");

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

void WidgetFunctional::on_pushButton_5_clicked()
{
    dlogin = new DLogin();
    dlogin->exec();
}

