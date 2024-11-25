#include "DPull.h"
#include "ui_DPull.h"

DPull::DPull(QString fileName, ServerManager* serverManager, QWidget *parent)
    :QDialog(parent), ui(new Ui::DPull), fileName(fileName), serverManager(serverManager)
{
    ui->setupUi(this);

    QFileInfo fileInfo(fileName);
    QString baseName = fileInfo.baseName();
    QString extension = fileInfo.suffix();

    // 定义正则表达式来提取文件名中的时间戳部分
    QRegularExpression regex("(.*?)(\\d{14})$");  // 匹配文件名中以14位数字结尾的时间戳部分
    QRegularExpressionMatch match = regex.match(baseName);

    if (match.hasMatch()) {
        QString fileCoreName = match.captured(1);  // 提取文件名（时间戳之前的部分）
        QString timeStamp = match.captured(2);     // 提取时间戳部分

        ui->lineEdit->setText(fileCoreName + "." + extension);

        QDateTime dateTime = QDateTime::fromString(timeStamp, "yyyyMMddHHmmss");
        ui->dateTimeEdit->setDateTime(dateTime);
    }
    else {
        qDebug() << "File name does not match expected pattern.";
    }
}

DPull::~DPull()
{
    delete ui;
}

void DPull::on_fastDlBtn_clicked()
{
    serverManager->downloadFile(fileName);
}


void DPull::on_dlBtn_clicked()
{

}


void DPull::on_dlBtn_2_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("选择保存目录"),
        QString(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    // 如果用户选择了目录，设置到lineEdit_2
    if (!dir.isEmpty()) {
        ui->lineEdit_2->setText(dir);
    }
}

