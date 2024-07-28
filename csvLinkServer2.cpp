#include "csvLinkServer2.h"
#include "ui_csvLinkServer2.h"
#include "EditedLog.h"
csvLinkServer::csvLinkServer(QWidget *parent): QWidget(parent),
        ui(new Ui::csvLinkServer2), tcpSocket(new QTcpSocket(this))
{
    ui->setupUi(this);

}

csvLinkServer::~csvLinkServer()
{
    delete ui;
    tcpSocket->disconnect();
    tcpSocket->waitForDisconnected();
    delete tcpSocket;
}

void csvLinkServer::bindTab(TabHandleCSV *eTableTab)
{
    m_tableTab = eTableTab;

    connect(m_tableTab, &TabHandleCSV::dataToSend, this, &csvLinkServer::sendDataToServer);

    connect(tcpSocket, &QTcpSocket::connected, this, []() {
        qDebug() << "Connected to server.";
    });
    connect(tcpSocket, &QTcpSocket::disconnected, this, []() {
        qDebug() << "Disconnected from server.";
    });
    connect(tcpSocket, &QTcpSocket::readyRead, this, &csvLinkServer::on_readyRead);
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
            m_tableTab->ReadfromServer(remainingData);
            return;
        }

        QString secondLine = lines.value(1);
        QString remainingData = data.mid(firstLine.length() + secondLine.length() + 2);
        ui->textBrowser->append("消息提示: " + secondLine + "--" + remainingData);
        if(firstLine == "chick")
        {
            m_tableTab->ChickfromServer(remainingData);
        }
        if(firstLine == "clear")
        {
            m_tableTab->clearfromServer(remainingData);
        }
        if(firstLine == "edited")
        {
            QString logMessage = QString("Edited: %1").arg(remainingData);
            EditedLog logger;
            logger.writeLog(logMessage);
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
    m_tableTab->setLinkStatus(false);
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

