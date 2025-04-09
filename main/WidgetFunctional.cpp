#include "./include/WidgetFunctional.h"
#include "ui/ui_WidgetFunctional.h"

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
    emit showFilebackup();
}


void WidgetFunctional::on_pushButton_3_clicked() {
    emit showWSchedule();

}


void WidgetFunctional::on_pushButton_4_clicked()
{
    emit showwOnlinedoc();

}

void WidgetFunctional::on_pushButton_5_clicked()
{
    emit showDraw();
}

void WidgetFunctional::on_pushButton_6_clicked()
{
    SendEmail *form = new SendEmail();
    emit sendEmailForm(form);
}

void WidgetFunctional::on_pushButton_7_clicked()
{
    dlogin = new DLogin();
    connect(dlogin, &DLogin::loginSuccessful, this, &WidgetFunctional::handleLoginSuccess);
    dlogin->exec();
}


void WidgetFunctional::on_pushButton_8_clicked()
{
    more_function = new MoreFunction();
    more_function->show();
}


void WidgetFunctional::on_pushButton_9_clicked()
{
    emit showClipboard(clipboard);
}



void WidgetFunctional::handleLoginSuccess(const QString& username) {
    qDebug() << "Username in handleLoginSuccess:" << username;
    dinfo = new DInfo(username, this);
}

WidgetFunctional::WidgetFunctional(QWidget *parent)
    : QWidget(parent), ui(new Ui::WidgetFunctional)
{
    ui->setupUi(this);
    btnGroup=new QButtonGroup;
    for (int i = 1; i <= 9; ++i) {
        QPushButton *button = findChild<QPushButton*>(QString("pushButton_%1").arg(i));        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

        if (button) {
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
            btnGroup->addButton(button);
            button->setCheckable(true);

            connect(button, &QPushButton::clicked, this, [=]() {
                foreach(QAbstractButton *btn, btnGroup->buttons()) {
                    btn->setChecked(btn->objectName() == QString("pushButton_%1").arg(i));
                }
            });
        }
    }

   this->setStyleSheet(
        // "QPushButton#pushButton_1, QPushButton#pushButton_2,"
        // "QPushButton#pushButton_3, QPushButton#pushButton_4,"
        // "QPushButton#pushButton_5, QPushButton#pushButton_6,"
        // "QPushButton#pushButton_7"
        // "{background:transparent;border:none;color:#000000;}"

        "QPushButton#pushButton_1:checked, QPushButton#pushButton_2:checked,"
        "QPushButton#pushButton_3:checked, QPushButton#pushButton_4:checked,"
        "QPushButton#pushButton_5:checked, QPushButton#pushButton_6:checked,"
        "QPushButton#pushButton_7:checked, QPushButton#pushButton_8:checked,"
        "QPushButton#pushButton_9:checked"
        "{background:transparent;border:none;   border-bottom:3px solid #3598db;color:#3598db;}"

        "QPushButton#pushButton_1:hover, QPushButton#pushButton_2:hover,"
        "QPushButton#pushButton_3:hover, QPushButton#pushButton_4:hover,"
        "QPushButton#pushButton_5:hover, QPushButton#pushButton_6:hover,"
        "QPushButton#pushButton_7:hover, QPushButton#pushButton_8:hover,"
        "QPushButton#pushButton_9:hover"
        "{background:transparent;border:none;   border-bottom:3px solid #7598db;color:#7598db;}"
    );

    // ui->pushButton_7->hide(); //暂时不隐藏
    clipboard = new ClipboardView();

}


void WidgetFunctional::toggleButtonVisibility(int buttonIndex)
{
    QPushButton *button = nullptr;
    switch (buttonIndex) {
    case 1: button = ui->pushButton_1; break;
    case 2: button = ui->pushButton_2; break;
    case 3: button = ui->pushButton_3; break;
    case 4: button = ui->pushButton_4; break;
    case 5: button = ui->pushButton_5; break;
    case 6: button = ui->pushButton_6; break;
    case 7: button = ui->pushButton_7; break;
    case 8: button = ui->pushButton_8; break;
    case 9: button = ui->pushButton_9; break;
    default: return;
    }

    if (button) {
        bool isVisible = button->isVisible();
        button->setVisible(!isVisible);
        emit buttonVisibilityChanged(buttonIndex, !isVisible);
    }
}
