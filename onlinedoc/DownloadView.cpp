#include "./include/DownloadView.h"
#include "ui/ui_DownloadView.h"

DownloadView::DownloadView(QWidget *parent) :QWidget(parent),
    ui(new Ui::DownloadView),reply(nullptr),downloadedFile(nullptr){

    ui->setupUi(this);
    ui->editURL->setClearButtonEnabled(true);

    QString curPath = QDir::currentPath();
    QDir dir(curPath);
    ui->editPath->setText(curPath + "/");
}

DownloadView::~DownloadView()
{
    delete ui;
}

void DownloadView::do_finished()
{
    QFileInfo fileInfo(downloadedFile->fileName());

    downloadedFile->close();
    reply->deleteLater();

    // 读取下载的文件内容
    downloadedFile->open(QIODevice::ReadOnly);
    QByteArray fileContent = downloadedFile->readAll();
    downloadedFile->close();

    // 发送信号，将文件名和内容传递出去

    delete downloadedFile;
    downloadedFile = nullptr;

    if (ui->chkBoxOpen->isChecked())
    {
        emit fileDownloaded(fileInfo.fileName(), fileContent);

    }
    ui->btnDownload->setEnabled(true);
}

void DownloadView::do_readyRead()
{
    downloadedFile->write(reply->readAll());
}

void DownloadView::do_downloadProgress(qint64 bytesRead, qint64 totalBytes)
{
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesRead);
}


void DownloadView::on_btnDefaultPath_clicked()
{
    QString defaultPath = QCoreApplication::applicationDirPath();
    QString directory = QFileDialog::getExistingDirectory(
        this, tr("选择文件夹"), defaultPath, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (directory.isEmpty())
        return;
    ui->editPath->setText(directory);
}

void DownloadView::on_btnDownload_clicked()
{
    QString urlSpec = ui->editURL->text().trimmed();
    if (urlSpec.isEmpty())
    {
        QMessageBox::information(this, "错误", "请指定需要下载的URL");
        return;
    }
    QUrl newUrl = QUrl::fromUserInput(urlSpec);
    if (!newUrl.isValid())
    {
        QString info = "无效URL:" + urlSpec + "\n错误信息:" + newUrl.errorString();
        QMessageBox::information(this, "错误", info);
        return;
    }
    QString tempDir = ui->editPath->text().trimmed();
    if (tempDir.isEmpty())
    {
        QMessageBox::information(this, "错误", "请指定保存下载文件的目录");
        return;
    }

    QString fullFileName = tempDir + newUrl.fileName();
    if (QFile::exists(fullFileName))
        QFile::remove(fullFileName);

    downloadedFile = new QFile(fullFileName);
    if (!downloadedFile->open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, "错误", "临时文件打开错误");
        return;
    }

    ui->btnDownload->setEnabled(false);
    reply = networkManager.get(QNetworkRequest(newUrl));
    connect(reply, SIGNAL(readyRead()), this, SLOT(do_readyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(do_downloadProgress(qint64, qint64)));
    connect(reply, SIGNAL(finished()), this, SLOT(do_finished()));
}


void DownloadView::on_editURL_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);
}
