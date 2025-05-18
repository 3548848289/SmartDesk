#include "include/TagList.h"
#include "ui/ui_TagList.h"

TagList::TagList(const FilePathInfo &fileInfo, QWidget *parent)
    : QWidget(parent), ui(new Ui::TagList), fileInfo(fileInfo)
{
    ui->setupUi(this);

    QFileInfo fileInfoObj(fileInfo.filePath);
    ui->fileLabel->setText(fileInfoObj.fileName());

    ui->lineEdit->setMaximumHeight(30);
    ui->lineEdit->setText(fileInfoObj.path());
    ui->lineEdit->setToolTip(fileInfoObj.path());

    ui->expirationLabel->setText(getExpInfo(fileInfo.expirationDate));
    ui->tagLabel->setText(fileInfo.tagName);
}



TagList::~TagList()
{
    delete ui;
}

QString TagList::getFilePath() const
{
    return fileInfo.filePath;
}

QString TagList::getExpInfo(const QDateTime expDate)
{
    QDateTime now = QDateTime::currentDateTime();
    QString expInfo;

    if (expDate.isValid()) {
        qint64 mnow = now.secsTo(expDate);
        if (mnow >= 0) {
            int s = mnow / 3600;        // 计算小时数
            int m = (mnow % 3600) / 60; // 计算分钟数
            expInfo = QString("%1:%2").arg(s, 2, 10, QChar('0')).arg(m, 2, 10, QChar('0'));
        } else {
            // int oh = -mnow / 3600;         // 计算小时数（过期时是负值）
            // int om = (-mnow % 3600) / 60;  // 计算分钟数（过期时是负值）
            // expInfo = QString("%1:%2").arg(oh, 2, 10, QChar('0')).arg(om, 2, 10, QChar('0'));
            expInfo = "已过期";
        }
    } else {
        expInfo = "No expiration date";
    }

    return expDate.isValid()
               ? expDate.toString("MM-dd hh:mm\n") + " (" + expInfo + ")" : expInfo;
}

void TagList::on_pushButton_clicked()
{
    TagDetail * tagdetail = new TagDetail(nullptr, fileInfo);
    tagdetail->show();
}

