#ifndef TAGLIST_H
#define TAGLIST_H

#include <QWidget>
#include <QString>
#include <QFileInfo>
#include <QDateTime>
#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QTableWidget>
#include "TagDetail.h"

#include "../../manager/include/dbService.h"

namespace Ui {
class TagList;
}


class TagList : public QWidget
{
    Q_OBJECT

public:
    explicit TagList(const FilePathInfo &fileInfo, QWidget *parent = nullptr);
    ~TagList();

    // 获取文件路径
    QString getFilePath() const;

    QString getExpInfo(const QDateTime expDate);
private slots:
    void on_pushButton_clicked();

private:
    Ui::TagList *ui;
    FilePathInfo fileInfo;
};

#endif // TAGLIST_H
