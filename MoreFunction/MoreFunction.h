#ifndef MOREFUNCTION_H
#define MOREFUNCTION_H

#include <QWidget>

namespace Ui {
class MoreFunction;
}

class MoreFunction : public QWidget
{
    Q_OBJECT

public:
    explicit MoreFunction(QWidget *parent = nullptr);
    ~MoreFunction();

private:
    Ui::MoreFunction *ui;
};

#endif // MOREFUNCTION_H
