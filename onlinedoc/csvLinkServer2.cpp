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
    QByteArray data = tcpSocket->readAll();
    QString fixedData = QString::fromUtf8(data).replace("\\\\u", "\\u");

    int bracePos = fixedData.lastIndexOf('}');
    int bracketPos = fixedData.lastIndexOf(']');
    int pos = qMax(bracePos, bracketPos);
    if (pos != -1) {
        fixedData = fixedData.left(pos + 1);
    }

    QByteArray fixedDataBytes = fixedData.toUtf8();

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fixedDataBytes, &parseError);

    QJsonObject jsonObj = jsonDoc.object();
    QString operation = jsonObj.value("operation").toString();
    ui->textBrowser->append("消息提示: " + jsonObj.value("ip").toString() + " -- " + operation);

    if (operation == "read") {
        m_tableTab->ReadfromServer(jsonObj);
    } else if (operation == "chick") {
        m_tableTab->ChickfromServer(jsonObj);
    } else if (operation == "clear") {
        m_tableTab->clearfromServer(jsonObj);
    } else if (operation == "edited") {

        m_tableTab->editedfromServer(jsonObj);
        EditedLog logger;
        logger.writeLog(jsonObj);
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
    QString filePath = ui->readfileEdit->text();
    if (!filePath.isEmpty())
    {

        QString jsonString = myJson::constructJson(localIp, "read",-1, -1, filePath);
        qDebug() << "Sending JSON data to server: " << jsonString;
        QByteArray data = jsonString.toUtf8();
        tcpSocket->write(data);
        ui->msgEdit->clear();
        emit filePathSent();
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
        localIp = tcpSocket->localAddress().toString();
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

