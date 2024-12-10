#include "./include/FileItemWidget.h"
#include "ui/ui_FileItemWidget.h"

FileItemWidget::FileItemWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::FileItemWidget)
{
    ui->setupUi(this);
}

FileItemWidget::~FileItemWidget()
{
    delete ui;
}

void FileItemWidget::setFileInfo(const QString &filePath, const QString &expirationInfo)
{
    this->filePath = filePath;

    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();
    QString fileDir = fileInfo.absolutePath();

    ui->fileLabel->setText(fileName);
    ui->pathLabel->setText(fileDir);
    ui->tagLabel->setText(tag);
    ui->expirationLabel->setText(expirationInfo);
}

QString FileItemWidget::getFilePath() const
{
    return filePath;
}

void FileItemWidget::setTag(const QString &mtag) {
    tag = mtag;
}
