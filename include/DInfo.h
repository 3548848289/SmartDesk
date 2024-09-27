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

//#include "ElaCalendarPicker.h"
#include "ElaComboBox.h"
#include "ElaLineEdit.h"
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

    QLabel* avatarLabel;
    QLabel* nameLabel;
    QLabel* mottoLabel;
    QLabel* genderLabel;
    QLabel* birthdayLabel;
    QLabel* locationLabel;
    QLabel* companyLabel;
    QLabel* accountLabel;
    ElaLineEdit* nameEdit;
    ElaLineEdit* accountEdit;
    ElaLineEdit* mottoEdit;
    ElaComboBox* genderCombo;
    QDateEdit* birthdayEdit;
    ElaLineEdit* locationEdit;
    ElaLineEdit* companyEdit;
    QPushButton* saveButton;


    void setupUi();

    void loadUserInfo();

    void saveUserInfo();


private:
    Ui::DInfo *ui;
};

#endif // DINFO_H


