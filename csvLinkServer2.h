#ifndef csvLinkServer_H
#define csvLinkServer_H

#include <QWidget>
#include <QTcpSocket>
#include <QMessageBox>
#include <QHostAddress>
#include <QNetworkProxy>
#include "TabHandleCSV.h"

QT_BEGIN_NAMESPACE
namespace Ui { class csvLinkServer2; }
QT_END_NAMESPACE

class csvLinkServer : public QWidget
{
    Q_OBJECT

public:
    csvLinkServer(QWidget *parent = nullptr);
    ~csvLinkServer();

    void bindTab(TabHandleCSV* tab);


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
    Ui::csvLinkServer2 *ui;
    QTcpSocket *tcpSocket;
    TabHandleCSV *m_tableTab;
};

#endif // csvLinkServer_H

