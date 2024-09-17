#ifndef WIDGETFUNCTIONAL_H
#define WIDGETFUNCTIONAL_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QButtonGroup>
#include "DLogin.h"
namespace Ui {
class WidgetFunctional;
}

class WidgetFunctional : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetFunctional(QWidget *parent = nullptr);
    ~WidgetFunctional();

signals:
    void showRU();
    void showRD();

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

private:
    QButtonGroup* btnGroup;
    QHBoxLayout* btnLayout;
    QVBoxLayout* mainLayout;
    DLogin * dlogin;
    Ui::WidgetFunctional *ui;
};

#endif // WIDGETFUNCTIONAL_H
