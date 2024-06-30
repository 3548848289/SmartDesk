
#include "Epoll.h"
#include "ui_epoll.h"
#include <QMessageBox>
#include <QHostAddress>
#include <QNetworkProxy>
Epoll::Epoll(QWidget *parent): QMainWindow(parent), ui(new Ui::Epoll), tcpSocket(new QTcpSocket(this))
{
    ui->setupUi(this);

    // Connect signals for debugging
    connect(tcpSocket, &QTcpSocket::connected, this, []() {
        qDebug() << "Connected to server.";
    });
    connect(tcpSocket, &QTcpSocket::disconnected, this, []() {
        qDebug() << "Disconnected from server.";
    });
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Epoll::on_readyRead); // Connect readyRead signal

//    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, [](QAbstractSocket::SocketError socketError){
//        qDebug() << "Socket error:" << socketError;
//    });
}

Epoll::~Epoll()
{
    delete ui;
}

void Epoll::on_pushButton_clicked()
{

    QString serverIp = "192.168.41.128";  // 服务器IP地址
    quint16 serverPort = 9190;

    tcpSocket->abort(); // 确保任何现有连接被中止
    tcpSocket->setProxy(QNetworkProxy::NoProxy); // 确保没有代理
    tcpSocket->connectToHost(serverIp, serverPort);

    if (!tcpSocket->waitForConnected(3000)) {
        QString errorString = tcpSocket->errorString();
        QMessageBox::warning(this, tr("Error"), tr("Failed to connect to server: %1").arg(errorString));
        qDebug() << "Connection error:" << errorString;
    } else {
        QMessageBox::information(this, tr("Connected"), tr("Connected to server"));
    }
}



void Epoll::on_readyRead()
{
    QByteArray data = tcpSocket->readAll();
    ui->textBrowser->append("Server: " + QString(data));
}

void Epoll::on_disconnected()
{
    QMessageBox::information(this, tr("Disconnected"), tr("Disconnected from server"));
}



void Epoll::on_pushButton_2_clicked()
{
    QString message = ui->lineEdit->text();
    if (!message.isEmpty()) {
        tcpSocket->write(message.toUtf8());
        ui->lineEdit->clear();
    }
}

