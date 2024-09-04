#ifndef WIDGETRU_H
#define WIDGETRU_H

#include <QWidget>

namespace Ui {
class WidgetRU;
}

class WidgetRU : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetRU(QWidget *parent = nullptr);
    ~WidgetRU();

private:
    Ui::WidgetRU *ui;
};

#endif // WIDGETRU_H
