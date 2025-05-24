#ifndef APPHELP_H
#define APPHELP_H

#include <QWidget>
#include <QLabel>
namespace Ui {
class AppHelp;
}

class AppHelp : public QWidget
{
    Q_OBJECT

public:
    explicit AppHelp(QWidget *parent = nullptr);
    ~AppHelp();

private:
    Ui::AppHelp *ui;
};

#endif // APPHELP_H
