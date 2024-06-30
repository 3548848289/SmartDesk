#ifndef TAB_H
#define TAB_H

#include <QWidget>
#include <QString>
namespace Ui {
class Tab;
}

class Tab : public QWidget
{
    Q_OBJECT

public:
    explicit Tab(QWidget *parent = nullptr);
    QString TabGetText();

    void TabSetText(const QString& text);

    ~Tab();

private:
    Ui::Tab *ui;
};

#endif // TAB_H
