#include "./include/SharedView.h"
#include "ui/ui_SharedView.h"
#include "EditedLog.h"

SharedView::SharedView(QWidget *parent): QWidget(parent),ui(new Ui::SharedView),
    tcpSocket(new QTcpSocket(this)),serverManager(ServerManager::instance()),
    dbservice(dbService::instance("./SmartDesk.db"))
{
    ui->setupUi(this);
}

SharedView::~SharedView()
{
    delete ui;
    tcpSocket->disconnect();
    tcpSocket->waitForDisconnected();
    delete tcpSocket;
}

void SharedView::bindTab(TabHandleCSV *eTableTab)
{
    m_tableTab = eTableTab;

    connect(m_tableTab, &TabHandleCSV::dataToSend, this, &SharedView::sendDataToServer);

    connect(tcpSocket, &QTcpSocket::connected, this, []() {
        qDebug() << "Connected to server.";
    });
    connect(tcpSocket, &QTcpSocket::disconnected, this, []() {
        qDebug() << "Disconnected from server.";
    });
    connect(tcpSocket, &QTcpSocket::readyRead, this, &SharedView::on_readyRead);
}

void SharedView::on_readyRead()
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

void SharedView::on_disconnected()
{
    QMessageBox::information(this, tr("Disconnected"), tr("Disconnected from server"));
}

void SharedView::sendDataToServer(const QString &data)
{
    if (tcpSocket->isOpen())
    {
        tcpSocket->write(data.toUtf8());
        tcpSocket->flush();
    }
}


void SharedView::on_sendmsgEdit_clicked()
{
    QString message = ui->msgEdit->text();
    if (!message.isEmpty()) {
        tcpSocket->write(message.toUtf8());
        ui->msgEdit->clear();
    }
}

void SharedView::on_linkserverBtn_clicked()
{

    QString serverIp = "192.168.188.236";
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

void SharedView::on_closeserverBtn_clicked()
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

void SharedView::on_passwdEdit_editingFinished()
{
    QString shareToken = ui->passwdEdit->text();
    if (shareToken.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("请输入共享口令！"));
        return;
    }

    QStringList files = dbservice.dbOnline().getSharedFilesByShareToken(shareToken);

    if (!files.isEmpty()) {
        ui->listWidget->clear();  // 清空现有的列表项

        for (const QString &file : files) {
            QStringList fileInfo = file.split(" ");
            if (fileInfo.size() >= 1) {
                ui->listWidget->addItem(fileInfo[0]);  // 添加文件名到列表
            }
        }
    } else {
        QMessageBox::warning(this, tr("警告"), tr("未找到对应的共享文件！"));
    }
}


void SharedView::on_listWidget_itemClicked(QListWidgetItem *item)
{
    on_linkserverBtn_clicked();
    int row = ui->listWidget->row(item);  // 获取当前项的行号
    QString filePath = item->text();  // 获取项的文本内容
    qDebug() << "Selected file path: " << filePath;

    QString jsonString = myJson::constructJson(localIp, "read", -1, -1, filePath);
    qDebug() << "Sending JSON data to server: " << jsonString;
    QByteArray data = jsonString.toUtf8();
    tcpSocket->write(data);
    ui->msgEdit->clear();
    emit filePathSent();
}


void SharedView::on_buildBtn_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("选择文件"), "", tr("All Files (*)"));
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("未选择任何文件！"));
        return;
    }

    QString fileName = QFileInfo(filePath).fileName();
    ui->readfileEdit_2->setText(filePath);

    QString shareToken = ui->passwdEdit->text();
    if (shareToken.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("请输入共享口令！"));
        return;
    }

    if (serverManager->commitFile(filePath))
        QMessageBox::information(this, tr("成功"), tr("文件上传成功，口令为：%1").arg(shareToken));
    else
        QMessageBox::warning(this, tr("警告"), tr("文件上传失败！"));
}


