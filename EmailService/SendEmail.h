#ifndef SENDEMAIL_H
#define SENDEMAIL_H

#include <QSettings>
#include <QWidget>
#include <QMenu>
#include <QTimer>
#include <QQueue>
namespace SimpleMail { class MimeMessage; class Server; }
namespace Ui { class SendEmail; }

using namespace SimpleMail;
class SendEmail : public QWidget
{
    Q_OBJECT

public:
    explicit SendEmail(QWidget *parent = nullptr);
    ~SendEmail();

    void sendEmailWithData(const QString &subject, const QString &bodyHtml, const QStringList &attachments);
private Q_SLOTS:
    void on_addAttachment_clicked();

    void on_sendEmail_clicked();
    void sendMailAsync(const MimeMessage &msg);

    void on_attachments_customContextMenuRequested(const QPoint &pos);

private:
    QSettings m_settings;
    std::vector<Server *> m_aServers;
    Ui::SendEmail *ui;

    void errorMessage(const QString &message);
    QQueue<MimeMessage> m_emailQueue;
    bool m_isSending = false;

    void processNextEmailInQueue();
};

#endif // SENDEMAIL_H
