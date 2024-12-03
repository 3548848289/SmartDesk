#include "./include/csvLinkServer2.h"
#include "ui/ui_csvLinkServer2.h"
#include "EditedLog.h"

csvLinkServer::csvLinkServer(QWidget *parent): QWidget(parent),ui(new Ui::csvLinkServer2),
    tcpSocket(new QTcpSocket(this)),serverManager(ServerManager::instance()),
    dbservice(dbService::instance("../SmartDesk.db"))
{
    ui->setupUi(this);
//    on_linkserverBtn_clicked();

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

void csvLinkServer::on_readfiieBtn_clicked() {
    QString shareToken = ui->passwdEdit->text();
    qDebug() << shareToken;
    if (shareToken.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("请输入共享口令！"));
        return;
    }

    QStringList files = dbservice.dbBackup().getSharedFilesByShareToken(shareToken);

    if (!files.isEmpty()) {
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(files.size());
        ui->tableWidget->setColumnCount(2);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << tr("远程文件名") << tr("本地文件路径"));

        for (int i = 0; i < files.size(); ++i) {
            QStringList fileInfo = files[i].split(" ");
            if (fileInfo.size() >= 2) {
                ui->tableWidget->setItem(i, 0, new QTableWidgetItem(fileInfo[0]));  // 远程文件名
                ui->tableWidget->setItem(i, 1, new QTableWidgetItem(fileInfo[1]));  // 本地路径
            }
        }
        ui->tableWidget->resizeColumnsToContents();
    } else {
        QMessageBox::warning(this, tr("警告"), tr("未找到对应的共享文件！"));
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

    QString serverIp = "192.168.240.236";
    QString portString = "9200";
    bool ok;
    quint16 serverPort = portString.toUShort(&ok);

    tcpSocket->abort();
    tcpSocket->setProxy(QNetworkProxy::NoProxy);
    tcpSocket->connectToHost(serverIp, serverPort);

    if (!tcpSocket->waitForConnected(3000)) {
        QString errorString = tcpSocket->errorString();
        QMessageBox::warning(this, tr("Error"), tr("Failed to connect to server: %1").arg(errorString));
    }
    else
    {
        //QMessageBox::information(this, tr("Connected"), tr("Connected to server"));
        localIp = tcpSocket->localAddress().toString();
    }
}

void csvLinkServer::on_closeserverBtn_clicked()
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

void csvLinkServer::on_pushButton_2_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("选择文件"), "", tr("CSV Files (*.csv);;All Files (*)"));

    if (filePath.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("未选择任何文件！"));
        return;
    }

    QString fileName = QFileInfo(filePath).fileName();
    ui->readfileEdit_2->setText(filePath);

    //
    //
    //
    //
    //
    //从用户界面输入框获取用户输入的口令,本来从数据库获取的，未完善
    //
    //
    //
    //
    QString shareToken = ui->passwdEdit->text();

    if (shareToken.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("请输入共享口令！"));
        return;
    }
    serverManager->commitToServer(filePath, "online/");
    if (dbservice.dbBackup().insertSharedFile(filePath, fileName, shareToken)) {
        QMessageBox::information(this, tr("成功"), tr("文件上传成功，口令为：%1").arg(shareToken));
    } else {
        QMessageBox::warning(this, tr("警告"), tr("文件上传失败！"));
    }
}


void csvLinkServer::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    int row = item->row();
    QTableWidgetItem *firstColumnItem = ui->tableWidget->item(row, 0);
    QString filePath;
    if (firstColumnItem)
    {
        filePath = firstColumnItem->text();
        qDebug() << "First column text: " << filePath;
    }

    QString jsonString = myJson::constructJson(localIp, "read", -1, -1, filePath);
    qDebug() << "Sending JSON data to server: " << jsonString;
    QByteArray data = jsonString.toUtf8();
    tcpSocket->write(data);
    ui->msgEdit->clear();
    emit filePathSent();
}
