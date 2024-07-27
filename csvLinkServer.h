#ifndef csvLinkServer_H
#define csvLinkServer_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QHostAddress>
#include <QNetworkProxy>
#include "TabHandleCSV.h"

QT_BEGIN_NAMESPACE
namespace Ui { class csvLinkServer; }
QT_END_NAMESPACE

class csvLinkServer : public QMainWindow
{
    Q_OBJECT

public:
    csvLinkServer(QWidget *parent = nullptr) : QMainWindow(parent)
    {

    }


    csvLinkServer(QWidget *parent, TabHandleCSV* eTableTab);
    ~csvLinkServer();


public slots:
    void sendDataToServer(const QString &data);

signals:
    void dataReceived(const QString &data);

private slots:
    void on_readyRead();
    void on_disconnected();


    void on_readfiieBtn_clicked();

    void on_sendmsgEdit_clicked();

    void on_linkserverBtn_clicked();

    void on_pushButton_clicked();

private:
    Ui::csvLinkServer *ui;
    QTcpSocket *tcpSocket;
    TabHandleCSV *tableTab;
};

#endif // csvLinkServer_H

