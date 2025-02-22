#ifndef TAGDETAIL_H
#define TAGDETAIL_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include "../../manager/include/dbService.h"

namespace Ui {
class TagDetail;
}

class TagDetail : public QWidget
{
    Q_OBJECT

public:
    explicit TagDetail(QWidget *parent, const FilePathInfo &fileInfo);
    ~TagDetail();

private slots:


    void on_choosePathBtn_clicked();

    void on_YesBtn_clicked();

    void on_deleteBtn_clicked();

private:
    void updateFileInfo();

    Ui::TagDetail *ui;
    dbService& dbservice;    // dbService 单例引用
    const FilePathInfo &fileInfo;  // 引用传递的文件路径信息
    QString oldFilePath ;
};

#endif // TAGDETAIL_H
