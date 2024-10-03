#include "./include/WidgetFunctional.h"
#include "ui/ui_WidgetFunctional.h"
#include "SimpleMail"

WidgetFunctional::~WidgetFunctional()
{
    delete ui;
}

DInfo* WidgetFunctional::getDInfo() {
    return dinfo;
}

void WidgetFunctional::on_pushButton_1_clicked() {
    emit showFiletag();
}

void WidgetFunctional::on_pushButton_2_clicked()
{
    emit showWSchedule();

}


void WidgetFunctional::on_pushButton_3_clicked() {
    emit showwOnlinedoc();
}


void WidgetFunctional::on_pushButton_4_clicked()
{
    emit showDraw();
}

void WidgetFunctional::on_pushButton_5_clicked()
{
    SendEmail *form = new SendEmail();
    emit sendEmailForm(form);
}

void WidgetFunctional::on_pushButton_6_clicked()
{

}

void WidgetFunctional::on_pushButton_7_clicked()
{
    dlogin = new DLogin(dbMysql);
    connect(dlogin, &DLogin::loginSuccessful, this, &WidgetFunctional::handleLoginSuccess);
    dlogin->exec();

}

void WidgetFunctional::handleLoginSuccess(const QString& username) {
    qDebug() << "Username in handleLoginSuccess:" << username;
    dinfo = new DInfo(username, dbMysql, this);
}




WidgetFunctional::WidgetFunctional(DBMySQL *dbInstance, QWidget *parent)
    : QWidget(parent), ui(new Ui::WidgetFunctional), dbMysql(dbInstance)
{
    ui->setupUi(this);
    btnGroup=new QButtonGroup;



    for (int i = 1; i <= 7; ++i) {
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
                        "QPushButton#pushButton_5, QPushButton#pushButton_6,"
                        "QPushButton#pushButton_7"
                        "{background:transparent;border:none;color:#000000;}"

                        "QPushButton#pushButton_1:checked, QPushButton#pushButton_2:checked,"
                        "QPushButton#pushButton_3:checked, QPushButton#pushButton_4:checked,"
                        "QPushButton#pushButton_5:checked, QPushButton#pushButton_6:checked,"
                        "QPushButton#pushButton_7:checked"
                        "{background:transparent;border:none;   border-bottom:3px solid #3598db;color:#3598db;}"

                        "QPushButton#pushButton_1:hover, QPushButton#pushButton_2:hover,"
                        "QPushButton#pushButton_3:hover, QPushButton#pushButton_4:hover,"
                        "QPushButton#pushButton_5:hover, QPushButton#pushButton_6:hover,"
                        "QPushButton#pushButton_7:hover"
                        "{background:transparent;border:none;   border-bottom:3px solid #7598db;color:#7598db;}");

}
