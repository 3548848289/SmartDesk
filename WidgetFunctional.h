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

private:
    Ui::WidgetFunctional *ui;
};

#endif // WIDGETFUNCTIONAL_H
