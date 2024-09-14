#ifndef WIDGETFUNCTIONAL_H
#define WIDGETFUNCTIONAL_H

#include <QWidget>

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
    void on_pushButton_2_clicked();

    void on_pushButton_1_clicked();

private:
    Ui::WidgetFunctional *ui;
};

#endif // WIDGETFUNCTIONAL_H
