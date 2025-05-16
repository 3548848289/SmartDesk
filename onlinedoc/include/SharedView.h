#ifndef SHAREVIEW_H
#define SHAREVIEW_H

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
#include <QListWidgetItem>

#include "../../manager/include/myJson.h"
#include "../../DisposeAbstract/DisposeCSV/TabHandleCSV.h"
#include "../../manager/include/ServerManager.h"
#include "../../manager/include/dbService.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SharedView; }
QT_END_NAMESPACE

class SharedView : public QWidget
{
    Q_OBJECT

public:
    SharedView(QWidget *parent = nullptr);
    ~SharedView();

    void bindTab(TabHandleCSV* tab);


public slots:
    void sendDataToServer(const QString &data);

signals:
    void dataReceived(const QString &data);
    void filePathSent();

private slots:
    void on_readyRead();
    void on_disconnected();
    void on_sendmsgEdit_clicked();
    void on_passwdEdit_editingFinished();

    void on_buildBtn_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    void on_linkserverBtn_clicked();
    void on_closeserverBtn_clicked();
    QString localIp;
    Ui::SharedView *ui;
    QTcpSocket *tcpSocket;
    TabHandleCSV *m_tableTab;
    dbService& dbservice;

};

#endif // SHAREVIEW_H

