#ifndef DLOGIN_H
#define DLOGIN_H

#include <QDialog>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QMouseEvent>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QToolButton>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QSqlError>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QFrame>
#include "../manager/DBMySQL.h"

#include "ElaPushButton.h"
#include "ElaLineEdit.h"
#include "ElaRadioButton.h"

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

private:
    QVBoxLayout *verticalLayout, *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_1, *horizontalLayout_2, *horizontalLayout_4;
    QLabel *statusLabel;
    QToolButton *exit_toolButton;
    ElaPushButton *avatar_pushButton, *login_pushButton, *resiger_pushButton, *forget_pushButton;
    QWidget *loginwidget;
    ElaLineEdit *username, *password;
    ElaRadioButton *radioButton;
    QFrame *line;

};

#endif // DLOGIN_H
