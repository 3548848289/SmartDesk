#ifndef WONLINEDOC_H
#define WONLINEDOC_H

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


private:
    Ui::WidgetRD *ui;
};

#endif // WONLINEDOC_H
