#ifndef DOWNLOADVIEW_H
#define DOWNLOADVIEW_H

#include <QFile>
#include <QDir>
#include <QWidget>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QMessageBox>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui {class DownloadView;}
QT_END_NAMESPACE
class DownloadView : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadView(QWidget *parent = nullptr);
    ~DownloadView();

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
    Ui::DownloadView *ui;
};

#endif // DOWNLOADVIEW_H
