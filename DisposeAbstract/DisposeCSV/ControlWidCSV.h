#ifndef CONTROLWIDCSV_H
#define CONTROLWIDCSV_H

#include <QObject>
#include <QPushButton>
#include <QList>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ControlWidCSV; }
QT_END_NAMESPACE

class ControlWidCSV : public QWidget {
    Q_OBJECT

public:
    explicit ControlWidCSV(QWidget *parent = nullptr);
    ~ControlWidCSV();

signals:
    // 定义信号，用于通知 TabHandleCSV 进行操作
    void addRowClicked();
    void deleteRowClicked();
    void addColumnClicked();
    void deleteColumnClicked();


private:
    Ui::ControlWidCSV *ui;  // UI 类的指针
};

#endif // CONTROLWIDCSV_H
