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

#include "../manager/DBMySQL.h"
namespace Ui {
class DInfo;
}

class DInfo : public QDialog
{
    Q_OBJECT

public:
    explicit DInfo(const QString& username, DBMySQL* dmMysql, QWidget* parent);

    ~DInfo();


private:
    QString username;
    DBMySQL* dmMysql;


    void setupUi();

    void loadUserInfo();

    void saveUserInfo();


private:
    Ui::DInfo *ui;
};

#endif // DINFO_H


