#ifndef DTAG_H
#define DTAG_H

#include <QDialog>

namespace Ui {
class DTag;
}

class DTag : public QDialog
{
    Q_OBJECT

public:
    explicit DTag(QWidget *parent = nullptr);

    QStringList getTagName() const;
    QString getAnnotation() const;
    QDateTime getExpirationDate() const;
    ~DTag();

private slots:
    void on_saveButton_clicked();

private:
    Ui::DTag *ui;
};

#endif // DTAG_H
