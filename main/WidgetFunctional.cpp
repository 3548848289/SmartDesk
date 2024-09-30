#include "WidgetFunctional.h"
#include "../ui/ui_WidgetFunctional.h"

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

WidgetFunctional::~WidgetFunctional()
{
    delete ui;
}

DInfo* WidgetFunctional::getDInfo() {
    return dinfo;
}

void WidgetFunctional::on_pushButton_1_clicked() {
    emit showRU();
}

void WidgetFunctional::on_pushButton_2_clicked()
{
    emit showWSchedule();

}


void WidgetFunctional::on_pushButton_3_clicked() {
    emit showRD();
}

void WidgetFunctional::on_pushButton_6_clicked()
{
    dlogin = new DLogin(dbMysql);
    connect(dlogin, &DLogin::loginSuccessful, this, &WidgetFunctional::handleLoginSuccess);
    dlogin->exec();

}


void WidgetFunctional::handleLoginSuccess(const QString& username) {
    qDebug() << "Username in handleLoginSuccess:" << username;

    dinfo = new DInfo(username, dbMysql, this);
}


void WidgetFunctional::on_pushButton_5_clicked()
{
//    auto server = new SimpleMail::Server;

//    // 使用 Gmail 的 SMTP 服务器（smtp.gmail.com，端口 465，SSL 连接）
//    server->setHost("smtp.qq.com");
//    server->setPort(465);
//    server->setConnectionType(SimpleMail::Server::SslConnection);

//    // 设置用户名（你的电子邮件地址）和 SMTP 认证密码
//    server->setUsername("3548848289@qq.com");
//    server->setPassword("gbwmwgxdepfvcjab");

//    // 创建一个 MimeMessage 对象，即邮件本身
//    SimpleMail::MimeMessage message;
//    message.setSender(SimpleMail::EmailAddress("M3548848289@outlook.com", "李阳坚QQ"));
//    message.addTo(SimpleMail::EmailAddress("李阳坚outlook"));
//    message.setSubject("测试主题");

//    // 创建一个 MimeText 对象
//    auto text = std::make_shared<SimpleMail::MimeText>();

//    // 向邮件中添加一些文本
//    text->setText("你好,\n这是一封简单的邮件。\n");

//    // 将其添加到邮件中
//    message.addPart(text);

//    // 发送邮件
//    SimpleMail::ServerReply *reply = server->sendMail(message);
//    QObject::connect(reply, &SimpleMail::ServerReply::finished, [reply] {
//        qDebug() << "ServerReply 完成" << reply->error() << reply->responseText();
//        reply->deleteLater();
//    });

}

