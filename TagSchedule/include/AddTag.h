#ifndef ADDTAG_H
#define ADDTAG_H

#include <QDialog>
#include <QDateTime>
namespace Ui {
class AddTag;
}

class AddTag : public QDialog
{
    Q_OBJECT

public:
    explicit AddTag(QWidget *parent = nullptr);

    QString getTagName() const;
    QString getAnnotation() const;
    QDateTime getExpirationDate() const;
    ~AddTag();

private slots:
    void on_saveButton_clicked();

private:
    Ui::AddTag *ui;
};

#endif // ADDTAG_H
