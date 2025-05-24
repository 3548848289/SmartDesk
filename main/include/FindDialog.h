#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = nullptr);
    ~FindDialog();
signals:
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);
    void findAll(const QString &str, Qt::CaseSensitivity cs);
    void dialogClosed();
protected:
    void closeEvent(QCloseEvent *event) override {
        emit dialogClosed();
        QDialog::closeEvent(event);
    }

private slots:
    void on_lineEdit_textChanged(const QString &arg1);
    void on_findButton_clicked();
    void on_findAllButton_clicked();

private:
    Ui::FindDialog *ui;
};

#endif // FINDDIALOG_H
