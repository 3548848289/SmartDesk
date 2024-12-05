#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QObject>
#include <QWidget>

class ControlWidget : public QWidget {
    Q_OBJECT
public:
    explicit ControlWidget(QWidget *parent = nullptr) : QWidget(parent) {}

    virtual void setupUI() = 0; // 这个方法让每个子类自己定义控件

};


#endif // CONTROLWIDGET_H
