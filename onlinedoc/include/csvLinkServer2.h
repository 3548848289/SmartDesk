#ifndef csvLinkServer_H
#define csvLinkServer_H

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkProxy>

#include <QWidget>
#include <QMessageBox>
#include <QRandomGenerator>

#include <QFileDialog>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include "../../manager/include/myJson.h"
#include "../../DisposeAbstract/DisposeCSV/TabHandleCSV.h"
#include "../../manager/include/ServerManager.h"
#include "../../manager/include/dbService.h"

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
    void filePathSent();

private slots:
    void on_readyRead();
    void on_disconnected();
    void on_readfiieBtn_clicked();
    void on_sendmsgEdit_clicked();
    void on_tableWidget_itemClicked(QTableWidgetItem *item);
    void on_buildBtn_clicked();

private:
    void on_linkserverBtn_clicked();
    void on_closeserverBtn_clicked();
    QString localIp;
    Ui::csvLinkServer2 *ui;
    QTcpSocket *tcpSocket;
    TabHandleCSV *m_tableTab;
    ServerManager* serverManager;
    dbService& dbservice;

};

#endif // csvLinkServer_H

