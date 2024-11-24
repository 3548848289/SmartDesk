#ifndef DLOGIN_H
#define DLOGIN_H

#include <QDialog>
#include <QImage>
#include <QPixmap>
#include <QMouseEvent>
#include <QJsonObject>
#include <QJsonDocument>
#include "D:\\QT6\\6.8.0\\mingw_64\include\\QtNetwork\\QNetworkAccessManager"
#include "D:\\QT6\\6.8.0\\mingw_64\include\\QtNetwork\\QNetworkRequest"
#include "D:\\QT6\\6.8.0\\mingw_64\include\\QtNetwork\\QNetworkReply"

#include <QMessageBox>
#include <QFileDialog>
#include <QBuffer>

#include "../../manager/include/DBMySQL.h"
#include "FlaskInfo.h"

namespace Ui {
class DLogin;
}

class DLogin : public QDialog
{
    Q_OBJECT

public:
    explicit DLogin(DBMySQL *dbmysql, QWidget *parent = nullptr);
    ~DLogin();

signals:
    void loginSuccessful(const QString &username);

private slots:
    void on_radioButton_clicked();
    void on_exit_toolButton_clicked();
    void on_avatar_pushButton_clicked();
    void on_registerBtn_clicked();
    void on_loginBtn_clicked();

    void onLoginResponse(const QJsonObject &response);
    void onRegisterResponse(const QJsonObject &response);
    void onNetworkError(const QString &error);
    void onAvatarDownloaded(const QByteArray &data, const QString &action);

private:
    Ui::DLogin *ui;                           // UI pointer
    FlaskInfo *flaskinfo;            // NetworkManager for handling requests

    QPixmap avatarImage;                      // Store avatar image
    QImage m_avatarImage;  // 用于保存头像图片


    DBMySQL *dbmysql;                         // Database object for interacting with MySQL
    bool mousePressed;                        // Flag for dragging the window
    QPoint startPos;                          // Start position for moving window

    // Private member functions for handling UI and network
    void handleLoginSuccess(const QJsonObject &jsonObject);
    void showMessage(const QString &title, const QString &message);
    QByteArray encodeAvatarImage();

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
};

#endif // DLOGIN_H
