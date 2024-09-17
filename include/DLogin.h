#ifndef DLOGIN_H
#define DLOGIN_H

#include <QDialog>
#include <QImage>
#include <QPixmap>
#include <QMouseEvent>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
namespace Ui {
class DLogin;
}

class DLogin : public QDialog
{
    Q_OBJECT

public:
    explicit DLogin(QWidget *parent = nullptr);
    ~DLogin();

private slots:
    void on_radioButton_clicked();
    void on_login_pushButton_clicked();
    void on_exit_toolButton_clicked();
    void on_avatar_pushButton_clicked();

private:
    Ui::DLogin *ui;

    QPixmap avatarImage;
    QSqlDatabase db;
    void registerUser(const QString &username, const QString &password);

    bool loginUser(const QString &username, const QString &password, QString &statusMessage);

    bool dbregisterUser(const QString &username, const QString &password, const QByteArray &avatarData, QString &statusMessage);

protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            mousePressed = true;
            startPos = event->globalPos() - this->frameGeometry().topLeft();
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (mousePressed) {
            move(event->globalPos() - startPos);
        }
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            mousePressed = false;
        }
    }

private:
    bool mousePressed;
    QPoint startPos;
};

#endif // DLOGIN_H
