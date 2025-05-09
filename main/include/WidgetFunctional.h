#ifndef WIDGETFUNCTIONAL_H
#define WIDGETFUNCTIONAL_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <memory>
#include <QDebug>

#include "../../userinfo/include/DLogin.h"
#include "../../manager/include/dbService.h"
#include "../../userinfo/include/DInfo.h"
#include "../../EmailService/SendEmail.h"
#include "../../MoreFunction/MoreFunction.h"
#include "../../ClipBoard/ClipboardView.h"


namespace Ui {
class WidgetFunctional;
}

class WidgetFunctional : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetFunctional(QWidget *parent = nullptr);
    ~WidgetFunctional();
    DInfo* getDInfo();

    void hideButton1();
    void toggleButtonVisibility(int buttonIndex);
signals:
    void showFiletag();
    void showFilebackup();
    void showwOnlinedoc();
    void showWSchedule();
    void sendEmailForm(SendEmail *form);
    void showDraw();
    void showClipboard(ClipboardView* clipboard);
    void buttonVisibilityChanged(int buttonIndex, bool isVisible);
public slots:
    void on_pushButton_7_clicked();

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();    
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_8_clicked();
    void handleLoginSuccess(const QString& username);

    void on_pushButton_9_clicked();

private:
    QButtonGroup* btnGroup;
    QHBoxLayout* btnLayout;
    QVBoxLayout* mainLayout;
    DLogin * dlogin;
    DInfo *dinfo;
    MoreFunction * more_function;
    ClipboardView* clipboard;

    Ui::WidgetFunctional *ui;
};

#endif // WIDGETFUNCTIONAL_H
