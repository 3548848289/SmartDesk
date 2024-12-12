#include "./include/TagList.h"
#include "ui/ui_TagList.h"

TagList::TagList(QWidget *parent) :
    QWidget(parent), ui(new Ui::TagList)
{
    ui->setupUi(this);
}

TagList::~TagList()
{
    delete ui;
}

void TagList::setFileInfo(const QString &filePath, const QString &expirationInfo)
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

QString TagList::getFilePath() const
{
    return filePath;
}

void TagList::setTag(const QString &mtag) {
    tag = mtag;
}
