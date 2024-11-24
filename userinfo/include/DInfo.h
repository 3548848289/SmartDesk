#ifndef DINFO_H
#define DINFO_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include <QPixmap>
#include <QDate>
#include <QMessageBox>
#include "FlaskInfo.h"

#include "../../manager/include/DBMySQL.h"
namespace Ui {
class DInfo;
}

class DInfo : public QDialog
{
    Q_OBJECT

public:
    explicit DInfo(const QString& username, DBMySQL* dmMysql, QWidget* parent);

    ~DInfo();
    QPixmap getStoredAvatar() const;


private slots:
    void on_saveButton_clicked();

private:
    QString username;
    DBMySQL* dmMysql;
    QPixmap storedAvatar;
    void setupUi();
    FlaskInfo* flaskinfo;
    void loadUserInfo(const QJsonObject &userInfo);
    void onUserInfoUpdated(const QJsonObject &response);
    void onErrorOccurred(const QString &error);

private:
    Ui::DInfo *ui;
};

#endif // DINFO_H


