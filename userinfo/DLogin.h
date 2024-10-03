#ifndef DLOGIN_H
#define DLOGIN_H
#include <QDialog>
#include <QImage>
#include <QPixmap>
#include <QMouseEvent>

#include "D:\\QT6\\6.6.0\\mingw_64\include\\QtSql\\QSqlDatabase"
#include "D:\\QT6\\6.6.0\\mingw_64\include\\QtSql\\QSqlQuery"
#include "D:\\QT6\\6.6.0\\mingw_64\include\\QtSql\\QSqlError"

#include <QMessageBox>
#include "../manager/include/DBMySQL.h"
namespace Ui {
class DLogin;
}

class DLogin : public QDialog
{
    Q_OBJECT

public:
    explicit DLogin(DBMySQL *dbInstance, QWidget *parent = nullptr);
    ~DLogin();

signals:
    void loginSuccessful(const QString& username);

private slots:
    void on_radioButton_clicked();
    void on_login_pushButton_clicked();
    void on_exit_toolButton_clicked();
    void on_avatar_pushButton_clicked();

private:
    Ui::DLogin *ui;

    QPixmap avatarImage;

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
    void registerUser(const QString &username, const QString &password);
    void onLogin();
    bool success = false;

    DBMySQL * db;
    bool mousePressed;
    QPoint startPos;
};

#endif // DLOGIN_H
