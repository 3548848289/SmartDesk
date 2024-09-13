#ifndef WIDGETRD_H
#define WIDGETRD_H

#include <QWidget>
#include <QPainter>
#include "DLfromNet.h"
#include "csvLinkServer2.h"

namespace Ui {
class WidgetRD;
}

class WidgetRD : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetRD(QWidget *parent = nullptr);
    ~WidgetRD();
    downLoad* downloadWidget;
    csvLinkServer* m_csvLinkServer;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::WidgetRD *ui;
};

#endif // WIDGETRD_H
