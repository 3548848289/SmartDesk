#ifndef Epoll_H
#define Epoll_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Epoll; }
QT_END_NAMESPACE

class Epoll : public QMainWindow
{
    Q_OBJECT

public:
    Epoll(QWidget *parent = nullptr);
    ~Epoll();

private slots:
    void on_readyRead();
    void on_disconnected();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Epoll *ui;
    QTcpSocket *tcpSocket;
};

#endif // Epoll_H

