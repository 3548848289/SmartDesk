#ifndef WIDGETFUNCTIONAL_H
#define WIDGETFUNCTIONAL_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QButtonGroup>
#include "../userinfo/DLogin.h"
#include "../manager/include/DBMySQL.h"
#include "../userinfo/DInfo.h"

#include <memory>
#include <QDebug>
#include "../../email/sendemail.h"
//#include "../draw/mainwidget.h"

namespace Ui {
class WidgetFunctional;
}

class WidgetFunctional : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetFunctional(DBMySQL *dbInstance, QWidget *parent = nullptr);
    ~WidgetFunctional();
    DInfo* getDInfo();

signals:
    void showFiletag();
    void showwOnlinedoc();
    void showWSchedule();
    void sendEmailForm(SendEmail *form);
    void showDraw();

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_2_clicked();
    void handleLoginSuccess(const QString& username);


    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_4_clicked();

private:
    QButtonGroup* btnGroup;
    QHBoxLayout* btnLayout;
    QVBoxLayout* mainLayout;
    DLogin * dlogin;
    DInfo *dinfo;
    DBMySQL *dbMysql;
    Ui::WidgetFunctional *ui;
};

#endif // WIDGETFUNCTIONAL_H
