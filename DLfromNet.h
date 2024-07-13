#ifndef DLFROMNET_H
#define DLFROMNET_H

#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {class downLoad;}
QT_END_NAMESPACE
class downLoad : public QMainWindow
{
    Q_OBJECT

public:
    explicit downLoad(QWidget *parent = nullptr);
    ~downLoad();

signals:
    void fileDownloaded(const QString &fileName, const QByteArray &fileContent);

private slots:
    void do_finished();
    void do_readyRead();
    void do_downloadProgress(qint64 bytesRead, qint64 totalBytes);
    void on_btnDefaultPath_clicked();
    void on_btnDownload_clicked();
    void on_editURL_textChanged(const QString &arg1);


private:
    QNetworkAccessManager networkManager;
    QNetworkReply *reply;
    QFile *downloadedFile;
    Ui::downLoad *ui;
};

#endif // DLFROMNET_H
