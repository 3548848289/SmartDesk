#ifndef DCOMMIT_H
#define DCOMMIT_H

#include <QDialog>

namespace Ui {
class DCommit;
}

class DCommit : public QDialog
{
    Q_OBJECT

public:
    explicit DCommit(QWidget *parent = nullptr);
    ~DCommit();

private:
    Ui::DCommit *ui;
};

#endif // DCOMMIT_H
