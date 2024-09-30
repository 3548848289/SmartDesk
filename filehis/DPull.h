#ifndef DPULL_H
#define DPULL_H

#include <QDialog>

namespace Ui {
class DPull;
}

class DPull : public QDialog
{
    Q_OBJECT

public:
    explicit DPull(QWidget *parent = nullptr);
    ~DPull();

private:
    Ui::DPull *ui;
};

#endif // DPULL_H
