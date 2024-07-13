#include "Epoll.h"
#include "ui_epoll.h"
#include <QMessageBox>
#include <QHostAddress>
#include <QNetworkProxy>


Epoll::Epoll(QWidget *parent, TableTab* eTableTab): QMainWindow(parent), ui(new Ui::Epoll),
    tcpSocket(new QTcpSocket(this)), tableTab(eTableTab)
{
    ui->setupUi(this);
    connect(tableTab, &TableTab::dataToSend, this, &Epoll::sendDataToServer);

    connect(tcpSocket, &QTcpSocket::connected, this, []() {
        qDebug() << "Connected to server.";
    });
    connect(tcpSocket, &QTcpSocket::disconnected, this, []() {
        qDebug() << "Disconnected from server.";
    });
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Epoll::on_readyRead);
}

Epoll::~Epoll()
{
    delete ui;
}


void Epoll::on_readyRead()
{
    QString data = tcpSocket->readAll();
    QStringList lines = data.split("\n");
    qDebug() << "这是读取的数据的首行内容" << lines.first();

    if (!lines.isEmpty()) {
        QString firstLine = lines.first();
        QString remainingData = data.mid(firstLine.length() + 1);
        ui->textBrowser->append("Server: " + firstLine);
        if(firstLine == "read")
        {
            tableTab->getEpolldata(remainingData);
        }
        if(firstLine == "chick")
        {
            tableTab->getEpolllight(remainingData);
        }
        if(firstLine == "clear")
        {
            tableTab->clearHighlight(remainingData);
        }
        if(firstLine == "edited")
        {
            tableTab->editCsvdata(remainingData);
        }
    }
}



void Epoll::on_disconnected()
{
    QMessageBox::information(this, tr("Disconnected"), tr("Disconnected from server"));
}


void Epoll::sendDataToServer(const QString &data)
{
    if (tcpSocket->isOpen())
    {
        tcpSocket->write(data.toUtf8());
        tcpSocket->flush();
    }
}

void Epoll::on_readfiieBtn_clicked()
{
    QString message = "read " + ui->readfileEdit->text();
    if (!message.isEmpty())
    {
        qDebug() << "Sending file path to server: " << message;
        tcpSocket->write(message.toUtf8());
        ui->msgEdit->clear();
    }
}


void Epoll::on_sendmsgEdit_clicked()
{
    QString message = ui->msgEdit->text();
    if (!message.isEmpty()) {
        tcpSocket->write(message.toUtf8());
        ui->msgEdit->clear();
    }
}


void Epoll::on_linkserverBtn_clicked()
{
    QString serverIp = ui->comboServer->currentText();
    quint16 serverPort = ui->spinPort->value();

    tcpSocket->abort();
    tcpSocket->setProxy(QNetworkProxy::NoProxy);
    tcpSocket->connectToHost(serverIp, serverPort);

    if (!tcpSocket->waitForConnected(3000)) {
        QString errorString = tcpSocket->errorString();
        QMessageBox::warning(this, tr("Error"), tr("Failed to connect to server: %1").arg(errorString));
    }
    else
    {
        QMessageBox::information(this, tr("Connected"), tr("Connected to server"));
    }
}

