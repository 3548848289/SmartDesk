#ifndef Http_H
#define Http_H

#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Http; }
QT_END_NAMESPACE

class Http : public QMainWindow
{
    Q_OBJECT

public:
    explicit Http(QWidget *parent = nullptr);
    ~Http();

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
    Ui::Http *ui;
    QNetworkAccessManager networkManager;
    QNetworkReply *reply;
    QFile *downloadedFile;
};

#endif // HTTP_H
