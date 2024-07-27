#include "csvLinkServer.h"
#include "ui_csvLinkServer.h"

csvLinkServer::csvLinkServer(QWidget *parent, TabHandleCSV* eTableTab): QMainWindow(parent), ui(new Ui::csvLinkServer),
    tcpSocket(new QTcpSocket(this)), tableTab(eTableTab)
{
    ui->setupUi(this);
    connect(tableTab, &TabHandleCSV::dataToSend, this, &csvLinkServer::sendDataToServer);

    connect(tcpSocket, &QTcpSocket::connected, this, []() {
        qDebug() << "Connected to server.";
    });
    connect(tcpSocket, &QTcpSocket::disconnected, this, []() {
        qDebug() << "Disconnected from server.";
    });
    connect(tcpSocket, &QTcpSocket::readyRead, this, &csvLinkServer::on_readyRead);
}

csvLinkServer::~csvLinkServer()
{
    delete ui;
    tcpSocket->disconnect();
    tcpSocket->waitForDisconnected();
    delete tcpSocket;
}


void csvLinkServer::on_readyRead()
{
    QString data = tcpSocket->readAll();

    QStringList lines = data.split("\n");
    if (!lines.isEmpty()) {
        QString firstLine = lines.first();
        if(firstLine == "read")
        {
            QString remainingData = data.mid(firstLine.length() + 1);
            tableTab->ReadfromServer(remainingData);
            return;
        }

        QString secondLine = lines.value(1);
        QString remainingData = data.mid(firstLine.length() + secondLine.length() + 2);
        ui->textBrowser->append("消息提示: " + secondLine + "--" + remainingData);
        if(firstLine == "chick")
        {
            tableTab->ChickfromServer(remainingData);
        }
        if(firstLine == "clear")
        {
            tableTab->clearfromServer(remainingData);
        }
        if(firstLine == "edited")
        {
            tableTab->editedfromServer(remainingData);
        }
    }
}



void csvLinkServer::on_disconnected()
{
    QMessageBox::information(this, tr("Disconnected"), tr("Disconnected from server"));
}


void csvLinkServer::sendDataToServer(const QString &data)
{
    if (tcpSocket->isOpen())
    {
        tcpSocket->write(data.toUtf8());
        tcpSocket->flush();
    }
}

void csvLinkServer::on_readfiieBtn_clicked()
{
    QString message = "read " + ui->readfileEdit->text();
    if (!message.isEmpty())
    {
        qDebug() << "Sending file path to server: " << message;
        tcpSocket->write(message.toUtf8());
        ui->msgEdit->clear();
    }
}


void csvLinkServer::on_sendmsgEdit_clicked()
{
    QString message = ui->msgEdit->text();
    if (!message.isEmpty()) {
        tcpSocket->write(message.toUtf8());
        ui->msgEdit->clear();
    }
}


void csvLinkServer::on_linkserverBtn_clicked()
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


void csvLinkServer::on_pushButton_clicked()
{
    tableTab->setLinkStatus(false);
    if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
        tcpSocket->disconnectFromHost();
        if (tcpSocket->state() == QAbstractSocket::UnconnectedState || tcpSocket->waitForDisconnected(3000)) {
            QMessageBox::information(this, tr("Disconnected"), tr("Disconnected from server"));
            this->close();
            delete this;

        } else {
            QMessageBox::warning(this, tr("Error"), tr("Failed to disconnect from server"));
        }
    } else {
        qDebug() << "Socket is not connected.";
    }
}

