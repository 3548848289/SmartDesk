#ifndef WONLINEDOC_H
#define WONLINEDOC_H

#include <QWidget>
#include <QPainter>
#include "DownloadView.h"
#include "SharedView.h"

namespace Ui {
class WOnlineDoc;
}

class WOnlineDoc : public QWidget
{
    Q_OBJECT

public:
    explicit WOnlineDoc(QWidget *parent = nullptr);
    ~WOnlineDoc();
    DownloadView* download_view;
    SharedView* shared_view;


private:
    Ui::WOnlineDoc *ui;
};

#endif // WONLINEDOC_H
