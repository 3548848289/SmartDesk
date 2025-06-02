#include "./include/SharedView.h"
#include "ui/ui_SharedView.h"
#include "EditedLog.h"

SharedView::SharedView(QWidget *parent)
    : QWidget(parent),ui(new Ui::SharedView), tcpSocket(new QTcpSocket(this))
{
    ui->setupUi(this);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &SharedView::on_readyRead);
    connect(tcpSocket, &QTcpSocket::disconnected, this, [this]() {
        QString ip = tcpSocket->peerAddress().toString();
        QMessageBox::information(this, tr("已断开连接"), tr("已与服务器断开连接"));
        ui->textBrowser->append("=> " + ip + " -- " + "disconnect");

        linkStatus = false;
    });
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, [this](const QString &text) {
        choosedFile = text;
    });

    connect(ui->yesBtn, &QPushButton::clicked, this, [this]{
        getSharedFile();
    });
    connect(ui->passwdEdit, &QLineEdit::editingFinished, this, [this]{
        getSharedFile();
    });

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
    ui->textBrowser->append("=> " + jsonObj.value("ip").toString() + " -- " + operation);

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
    } else if (operation == "disconnect") {
        qDebug() << jsonObj;
    }

}

void SharedView::sendDataToServer(const QString &data)
{
    if (tcpSocket->isOpen())
    {
        tcpSocket->write(data.toUtf8());
        tcpSocket->flush();
    }
}

void SharedView::on_sendmsgBtn_clicked()
{
    QString message = ui->msgEdit->text();
    if (!message.isEmpty()) {
        tcpSocket->write(message.toUtf8());
        ui->msgEdit->clear();
    }
}

void SharedView::getSharedFile()
{
    QString shareToken = ui->passwdEdit->text();
    if (shareToken.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("请输入共享口令！"));
        return;
    }
    ServerManager::instance()->getSharedFile(shareToken);
    connect(ServerManager::instance(), &ServerManager::historyReceived, this, [=](const QStringList& files){
        if (!files.isEmpty()) {
            ui->comboBox->clear();
            for (const QString &file : files) {
                QStringList fileInfo = file.split(" ");
                if (fileInfo.size() >= 1)
                    ui->comboBox->addItem(fileInfo[0]);
            }
            ui->comboBox->setCurrentIndex(0);
        }
        else
            QMessageBox::warning(this, tr("警告"), tr("未找到对应的共享文件！"));
    });
}

void SharedView::on_buildBtn_clicked()
{
    QString shareToken = ui->createEdit->text().trimmed();
    if (shareToken.isEmpty()) {
        QMessageBox::warning(this, "", tr("共享口令不能为空，请输入一个口令。"));
        ui->createEdit->setFocus();
        return;
    }

    QString filePath = ui->readfileEdit_2->text();
    bool success = ServerManager::instance()->setSharedFile(filePath, shareToken);
    if (!success)
        QMessageBox::critical(this,tr("上传失败"),tr("请检查网络或稍后重试。"));
}


void SharedView::on_selectBtn_clicked()
{
    QString filePath =
        QFileDialog::getOpenFileName(this, tr("选择要共享的文件"), QDir::homePath(),tr("所有文件 (*.*)"));
    if (filePath.isEmpty()) {
        QMessageBox::information(this, tr("提示"), tr("您未选择任何文件。"));
        return;
    }

    ui->readfileEdit_2->setText(filePath);
}

void SharedView::on_closeBtn_clicked()
{
    if (m_tableTab != nullptr)
        m_tableTab->setLinkStatus(false);

    if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
        tcpSocket->disconnectFromHost();
    } else {
        QMessageBox::information(this, tr(""), tr("还没连接到服务器"));
    }
}

void SharedView::on_linkBtn_clicked()
{
    if(linkStatus){
        QMessageBox::information(this,"",tr("已连接至服务器"));
        return;
    }

    QString serverAddress = SettingManager::Instance().serverconfig_ip3();
    QUrl url(serverAddress);
    QString serverIp = url.host();
    int serverPort = url.port();
    tcpSocket->abort();
    tcpSocket->setProxy(QNetworkProxy::NoProxy);
    tcpSocket->connectToHost(serverIp, serverPort);


    if (!tcpSocket->waitForConnected(3000)) {
        QString errorString = tcpSocket->errorString();
        QMessageBox::warning(this, tr("错误"), tr("无法连接到服务器: %1").arg(errorString));
        return;
    }
    else{
        localIp = tcpSocket->localAddress().toString();
        linkStatus = true;
    }

    QString jsonString = myJson::constructJson(localIp, "read", -1, -1, choosedFile);
    QByteArray data = jsonString.toUtf8();
    tcpSocket->write(data);
    ui->msgEdit->clear();
    emit filePathSent();
}





