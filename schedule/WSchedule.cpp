#include "WSchedule.h"
#include "ui_WSchedule.h"
#include <QDesktopServices>
#include <QUrl>
#include <QListWidgetItem>
#include "./FileItemWidget.h"
#include <QTimer>
#include <QMessageBox>

WSchedule::WSchedule(DBSQlite *db, QWidget *parent) :
    QWidget(parent), ui(new Ui::WSchedule), db(db)
{
    ui->setupUi(this);
    filterByTag("刷新");
    loadTags();

    connect(ui->listWidget, &QListWidget::itemClicked, this, &WSchedule::onItemClicked);
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &WSchedule::onTagChanged);
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &WSchedule::onSearch);

    // 启动定时器检查到期文件
    startExpirationCheck();
}

WSchedule::~WSchedule()
{
    delete ui;
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
    ui->comboBox->addItem("刷新");

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
            int s = mnow / 3600;        // 计算小时数
            int m = (mnow % 3600) / 60; // 计算分钟数
            expInfo = QString("%1:%2").arg(s, 2, 10, QChar('0')).arg(m, 2, 10, QChar('0'));
        } else {
            int oh = -mnow / 3600;         // 计算小时数（过期时是负值）
            int om = (-mnow % 3600) / 60;  // 计算分钟数（过期时是负值）
            expInfo = QString("%1:%2").arg(oh, 2, 10, QChar('0')).arg(om, 2, 10, QChar('0'));
        }
    } else {
        expInfo = "No expiration date";
    }

    return expDate.isValid()
               ? expDate.toString("MM-dd hh:mm\n") + " (" + expInfo + ")" : expInfo;
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

void WSchedule::startExpirationCheck() {
    expirationTimer = new QTimer(this);
    connect(expirationTimer, &QTimer::timeout, this, &WSchedule::checkExpiration);
    expirationTimer->start(1800000);  // 每30分钟（30 * 60 * 1000毫秒）
}

void WSchedule::checkExpiration() {
    QList<FilePathInfo> files = db->getFilePathsByTag("刷新");

    for (const auto &file : files) {
        QString path = file.filePath;
        QDateTime expDate = file.expirationDate;

        // 如果文件即将到期，弹出提醒
        if (expDate.isValid() && QDateTime::currentDateTime().secsTo(expDate) <= 2 * 3600) {  // 2小时内到期
            QMessageBox::information(this, "Expiration Reminder",
                                     "File is expiring soon: " + path);
        }
    }
}
