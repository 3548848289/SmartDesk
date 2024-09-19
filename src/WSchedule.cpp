#include "WSchedule.h"
#include "../ui/ui_WSchedule.h"
#include <QDesktopServices>
#include <QUrl>
#include <QListWidgetItem>
#include "./FileItemWidget.h"

WSchedule::WSchedule(DatabaseManager *db, QWidget *parent) :
    QWidget(parent), ui(new Ui::WSchedule), db(db)
{
    ui->setupUi(this);

    filterByTag("标签");
    loadTags();

    connect(ui->listWidget, &QListWidget::itemClicked, this, &WSchedule::onItemClicked);
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &WSchedule::onTagChanged);
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &WSchedule::onSearch);
}

WSchedule::~WSchedule()
{
    delete ui;
    delete db;
}

void WSchedule::onItemClicked(QListWidgetItem *item) {
    FileItemWidget *widget = qobject_cast<FileItemWidget *>(ui->listWidget->itemWidget(item));
    if (widget) {
        QString path = widget->getFilePath();
        emit fileClicked(path);
    }
}

void WSchedule::loadTags() {
    ui->comboBox->clear();
    ui->comboBox->addItem("标签");

    QStringList tags = db->getAllTags();
    for (const QString &tag : tags) {
        ui->comboBox->addItem(tag);
    }
}

void WSchedule::filterByTag(const QString &tag) {
    ui->listWidget->clear();

    QList<FilePathInfo> files = db->getFilePathsByTag(tag);

    for (const auto &info : files) {
        QString path = info.filePath;
        QString tag = info.tagName;
        QDateTime expDate = info.expirationDate;

        FileItemWidget *widget = new FileItemWidget();
        qDebug() << tag;
        widget->setTag(tag);

        QString expInfo = getExpInfo(path, expDate);
        widget->setFileInfo(path, expInfo);

        QListWidgetItem *listItem = new QListWidgetItem(ui->listWidget);
        listItem->setSizeHint(widget->sizeHint());
        ui->listWidget->addItem(listItem);
        ui->listWidget->setItemWidget(listItem, widget);
    }
}

QString WSchedule::getExpInfo(const QString &path, const QDateTime &expDate) {
    QDateTime now = QDateTime::currentDateTime();
    QString expInfo;

    if (expDate.isValid()) {
        qint64 mnow = now.secsTo(expDate);
        if (mnow >= 0) {
            int s = mnow/3600, m = mnow % 3600 / 60, fin = mnow % 60;
            expInfo = QString("%1:%2:%3") .arg(s, 2, 10, QChar('0'))
                                          .arg(m, 2, 10, QChar('0')).arg(fin, 2, 10, QChar('0'));
        } else {
            int oh = -mnow / 3600, om = (-mnow % 3600) / 60, os = -mnow % 60;
            expInfo = QString("%1:%2:%3").arg(oh, 2, 10, QChar('0'))
                                         .arg(om, 2, 10, QChar('0')).arg(os, 2, 10, QChar('0'));
        }
    } else {
        expInfo = "No expiration date";
    }

    return expDate.isValid()
               ? expDate.toString("yyyy-MM-dd hh:mm:ss\n") + " (" + expInfo + ")" : expInfo;
}

void WSchedule::sortByExpDate() {
    ui->listWidget->clear();
    QVector<QPair<QString, QDateTime>> files = db->getSortByExp();

    for (const auto &file : files) {
        QString path = file.first;
        QDateTime expDate = file.second;

        FileItemWidget *widget = new FileItemWidget();
        widget->setFileInfo(path, getExpInfo(path, expDate));

        QListWidgetItem *listItem = new QListWidgetItem(ui->listWidget);
        listItem->setSizeHint(widget->sizeHint());
        ui->listWidget->addItem(listItem);
        ui->listWidget->setItemWidget(listItem, widget);
    }
}

void WSchedule::onTagChanged(const QString &tag) {
    filterByTag(tag);
}

void WSchedule::onSearch(const QString &keyword) {
    filterByKeyword(keyword);
}

void WSchedule::filterByKeyword(const QString &keyword) {
    ui->listWidget->clear();
    QStringList paths = db->searchFiles(keyword);

    for (const QString &path : paths) {
        FileItemWidget *widget = new FileItemWidget();
        widget->setFileInfo(path, "No expiration date");

        QListWidgetItem *listItem = new QListWidgetItem(ui->listWidget);
        listItem->setSizeHint(widget->sizeHint());
        ui->listWidget->addItem(listItem);
        ui->listWidget->setItemWidget(listItem, widget);
    }
}

void WSchedule::onSortClicked()
{
    sortByExpDate();
}

void WSchedule::on_pushButton_clicked()
{
    sortByExpDate();
}

