#include "WSchedule.h"
#include "../ui/ui_WSchedule.h"
#include <QStandardItemModel>
#include <QDesktopServices>
#include <QUrl>

WSchedule::WSchedule(DatabaseManager * dbManager, QWidget *parent) : QWidget(parent), ui(new Ui::WSchedule),
    dbManager(dbManager), model(new QStandardItemModel(this))
{
    ui->setupUi(this);

    ui->listView->setModel(model);

    loadFilesFromDatabase();
    loadTagsIntoComboBox();

    // 连接信号槽
    connect(ui->listView, &QListView::clicked, this, &WSchedule::onFileClicked);
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &WSchedule::onTagSelected);
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &WSchedule::onSearchTextChanged);
    connect(ui->sortButton, &QPushButton::clicked, this, &WSchedule::sortByExpirationDate);

}


void WSchedule::sortByExpirationDate() {
    model->clear(); // 清空模型
    QDate currentDate = QDate::currentDate(); // 获取当前日期

    // 从 dbManager 获取按到期时间排序的文件列表
    QVector<QPair<QString, QDate>> files = dbManager->getFilesSortedByExpiration();

    for (const auto &file : files) {
        QString filePath = file.first;
        QDate expirationDate = file.second;

        // 计算剩余天数
        int daysRemaining = currentDate.daysTo(expirationDate);

        // 构建显示的字符串
        QString displayText = filePath + " - Expiration: " + expirationDate.toString("yyyy-MM-dd");

        if (daysRemaining >= 0) {
            displayText += " (" + QString::number(daysRemaining) + " days remaining)";
        } else {
            displayText += " (Expired " + QString::number(-daysRemaining) + " days ago)";
        }

        // 创建列表项
        QStandardItem *item = new QStandardItem(displayText);
        model->appendRow(item);
    }

    ui->listView->setModel(model); // 更新 listView 显示
}


WSchedule::~WSchedule()
{
    delete ui;
    delete dbManager;
}

void WSchedule::loadFilesFromDatabase() {
    QStringList filePaths = dbManager->getAllFilePaths();
    for (const QString &filePath : filePaths) {
        QStandardItem *item = new QStandardItem(filePath);
        model->appendRow(item);
    }
}

void WSchedule::onFileClicked(const QModelIndex &index) {
    QString filePath = model->itemFromIndex(index)->text();
    emit fileClicked(filePath);

}
void WSchedule::loadTagsIntoComboBox() {
    ui->comboBox->clear();
    ui->comboBox->addItem("All Tags");

    QStringList tags = dbManager->getAllTags();
    for (const QString &tag : tags) {
        ui->comboBox->addItem(tag);
    }
}

void WSchedule::onTagSelected(const QString &tag) {
    if (tag == "All Tags") {
        loadFilesFromDatabase();
    } else {
        filterFilesByTag(tag);
    }
}

void WSchedule::filterFilesByTag(const QString &tag) {
    model->clear();
    QStringList filePaths = dbManager->getFilePathsByTag(tag);
    for (const QString &filePath : filePaths) {
        QStandardItem *item = new QStandardItem(filePath);
        model->appendRow(item);
    }
}
void WSchedule::onSearchTextChanged(const QString &keyword) {
    filterFilesByKeyword(keyword);
}

void WSchedule::filterFilesByKeyword(const QString &keyword) {
    model->clear();
    QStringList filePaths = dbManager->searchFiles(keyword);
    for (const QString &filePath : filePaths) {
        QStandardItem *item = new QStandardItem(filePath);
        model->appendRow(item);
    }
}



