#include "include/TagDetail.h"
#include "ui/ui_TagDetail.h"

TagDetail::TagDetail(QWidget *parent, const FilePathInfo &fileInfo)
    : QWidget(parent), fileInfo(fileInfo), ui(new Ui::TagDetail)
    , dbservice(dbService::instance("./SmartDesk.db"))

{
    ui->setupUi(this);
    qDebug() << fileInfo.filePath;

    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnCount(2);

    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("文件路径"));
    ui->tableWidget->setItem(1, 0, new QTableWidgetItem("标签"));
    ui->tableWidget->setItem(2, 0, new QTableWidgetItem("过期时间"));
    ui->tableWidget->setItem(3, 0, new QTableWidgetItem("备注"));
    ui->tableWidget->setItem(4, 0, new QTableWidgetItem("文件状态"));

    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(fileInfo.filePath));
    QTableWidgetItem *tagItem = new QTableWidgetItem(fileInfo.tagName);
    ui->tableWidget->setItem(1, 1, tagItem);

    ui->tableWidget->setItem(2, 1, new QTableWidgetItem(fileInfo.expirationDate.toString("yyyy-MM-ddTHH:mm:ss.zzz")));
    ui->tableWidget->setItem(3, 1, new QTableWidgetItem(fileInfo.annotation));
    QFileInfo fileInfoCheck(fileInfo.filePath);
    if (!fileInfoCheck.exists()) {
        ui->tableWidget->setItem(4, 1, new QTableWidgetItem("文件不存在"));
    } else {
        ui->tableWidget->setItem(4, 1, new QTableWidgetItem("文件存在"));
    }
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();

}

TagDetail::~TagDetail()
{
    delete ui;
}


void TagDetail::on_choosePathBtn_clicked()
{
    QString newPath = QFileDialog::getExistingDirectory(this, "选择新文件夹", "", QFileDialog::ShowDirsOnly);

    if (!newPath.isEmpty()) {
        oldFilePath = fileInfo.filePath;
        ui->tableWidget->item(0, 1)->setText(newPath);
        QFileInfo fileInfoCheck(fileInfo.filePath);
        if (!fileInfoCheck.exists()) {
            ui->tableWidget->item(4, 1)->setText("文件夹不存在");
        } else {
            ui->tableWidget->item(4, 1)->setText("文件夹存在");
        }

    }
}



void TagDetail::on_YesBtn_clicked()
{
    QString filePath = ui->tableWidget->item(0, 1)->text();
    QString newTag = ui->tableWidget->item(1, 1)->text();
    QString newDate = ui->tableWidget->item(2, 1)->text();
    QString newAnnotation = ui->tableWidget->item(3, 1)->text();

    if(filePath != oldFilePath)
    {
        bool judge = dbservice.dbTags().updateFilePath(filePath, oldFilePath);
        if (!judge) {
            QMessageBox::warning(this, "警告", "更新文件夹路径失败");
            return;
        }
    }

    if (newTag.isEmpty()) {
        QMessageBox::warning(this, "警告", "标签不能为空！");
        return;
    }
    QDateTime updateDate = QDateTime::fromString(newDate, "yyyy-MM-ddTHH:mm:ss.zzz");
    if (!updateDate.isValid() && !newDate.isEmpty()) {
        QMessageBox::warning(this, "警告", "过期时间格式无效！");
        return;
    }

    FilePathInfo fileInfo;
    fileInfo.filePath = filePath;
    fileInfo.tagName = newTag;
    fileInfo.expirationDate = updateDate;
    fileInfo.annotation = newAnnotation;

    bool judge = dbservice.dbTags().updateFileInfo(fileInfo);
    if (judge)
        close();
    else
        QMessageBox::warning(this, "更新失败", "更新标签和文件信息失败！");
}

void TagDetail::on_deleteBtn_clicked() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除", "确认删除标签、批注吗?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        int fileId;
        if (!dbservice.dbTags().getFileId(fileInfo.filePath, fileId)) {
            QMessageBox::warning(this, "错误", "无法找到文件ID！");
            return;
        }
        bool result = dbservice.dbTags().deleteTag(fileId);

        if (!result)
            QMessageBox::warning(this, "删除失败", "删除过程中出现错误，操作已回滚。");
        close();
    }
}
