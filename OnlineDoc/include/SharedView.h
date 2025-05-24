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
#include "../../Setting/include/SettingManager.h"

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
    void on_sendmsgBtn_clicked();
    void getSharedFile();
    void on_buildBtn_clicked();
    void on_closeBtn_clicked();
    void on_linkBtn_clicked();
    void on_selectBtn_clicked();

private:
    QString localIp;
    QString choosedFile;
    Ui::SharedView *ui;
    QTcpSocket *tcpSocket;
    TabHandleCSV *m_tableTab;

    bool linkStatus = false;

};

#endif // SHAREVIEW_H

