#ifndef WONLINEDOC_H
#define WONLINEDOC_H

#include <QWidget>
#include <QPainter>
#include "DLfromNet.h"
#include "csvLinkServer2.h"

namespace Ui {
class WOnlineDoc;
}

class WOnlineDoc : public QWidget
{
    Q_OBJECT

public:
    explicit WOnlineDoc(QWidget *parent = nullptr);
    ~WOnlineDoc();
    downLoad* downloadWidget;
    csvLinkServer* m_csvLinkServer;


private:
    Ui::WOnlineDoc *ui;
};

#endif // WONLINEDOC_H
