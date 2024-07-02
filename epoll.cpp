
#include "Epoll.h"
#include "ui_epoll.h"
#include <QMessageBox>
#include <QHostAddress>
#include <QNetworkProxy>


Epoll::Epoll(QWidget *parent, TableTab* eTableTab): QMainWindow(parent), ui(new Ui::Epoll),
    tcpSocket(new QTcpSocket(this)), tableTab(eTableTab)
{
    ui->setupUi(this);

    connect(tcpSocket, &QTcpSocket::connected, this, []() {
        qDebug() << "Connected to server.";
    });
    connect(tcpSocket, &QTcpSocket::disconnected, this, []() {
        qDebug() << "Disconnected from server.";
    });
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Epoll::on_readyRead);
    connect(tableTab, &TableTab::dataToSend, this, &Epoll::sendDataToServer);


}

Epoll::~Epoll()
{
    delete ui;
}

void Epoll::on_pushButton_clicked()
{
    QString serverIp = ui->comboServer->currentText();
    quint16 serverPort = ui->spinPort->value();

    tcpSocket->abort();                          // 确保任何现有连接被中止
    tcpSocket->setProxy(QNetworkProxy::NoProxy); // 确保没有代理
    tcpSocket->connectToHost(serverIp, serverPort);

    if (!tcpSocket->waitForConnected(3000)) {
        QString errorString = tcpSocket->errorString();
        QMessageBox::warning(this, tr("Error"), tr("Failed to connect to server: %1").arg(errorString));
    }
    else
        QMessageBox::information(this, tr("Connected"), tr("Connected to server"));
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


void Epoll::sendDataToServer(const QString &data)
{
    // Function to send data over tcpSocket
    if (tcpSocket->isOpen())
    {
        tcpSocket->write(data.toUtf8());
        tcpSocket->flush();
    }
}

