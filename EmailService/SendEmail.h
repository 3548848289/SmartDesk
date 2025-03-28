#ifndef SENDEMAIL_H
#define SENDEMAIL_H

#include "./simple-mail/src/SimpleMail"
#include <QSettings>
#include <QWidget>
#include <QMenu>

namespace Ui {
class SendEmail;
}

namespace SimpleMail {
class Server;
}

using namespace SimpleMail;

class SendEmail : public QWidget
{
    Q_OBJECT

public:
    explicit SendEmail(QWidget *parent = nullptr);
    ~SendEmail();

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
};

#endif // SENDEMAIL_H
