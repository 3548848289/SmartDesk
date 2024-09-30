#ifndef WFILEHIS_H
#define WFILEHIS_H

#include <QWidget>

namespace Ui {
class WFileHis;
}

class WFileHis : public QWidget
{
    Q_OBJECT

public:
    explicit WFileHis(QWidget *parent = nullptr);
    ~WFileHis();

private:
    Ui::WFileHis *ui;
};

#endif // WFILEHIS_H
