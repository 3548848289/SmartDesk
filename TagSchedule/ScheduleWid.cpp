#include "./include/ScheduleWid.h"
#include "ui/ui_ScheduleWid.h"

ScheduleWid::ScheduleWid(QWidget *parent) : QWidget(parent), ui(new Ui::ScheduleWid),
    dbservice(dbService::instance("../SmartDesk.db"))
{
    ui->setupUi(this);
    filterByTag("刷新");
    loadTags();

    connect(ui->listWidget, &QListWidget::itemClicked, this, &ScheduleWid::onItemClicked);
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &ScheduleWid::onSearch);

    // 启动定时器检查到期文件
    startExpirationCheck();

    manager = new NotifyManager(this);
    manager->setMaxCount(5);
    manager->setDisplayTime(10000);
    manager->setNotifyWndSize(300, 80);
    connect(manager, &NotifyManager::notifyDetail, [](const QVariantMap &data){
        QMessageBox msgbox(QMessageBox::Information, QStringLiteral("新消息"), data.value("title").toString());


        QStringList tagList = data.value("tag").toStringList();
        QString allDetails = data.value("body").toString() + "\n\n" + "Tags: " + tagList.join(", ") + "\n" +
                             "Annotation: " + data.value("annotation").toString();

        msgbox.setInformativeText(allDetails);
        msgbox.findChild<QDialogButtonBox*>()->setMinimumWidth(500);
        msgbox.exec();
    });
    checkExpiration();
}

ScheduleWid::~ScheduleWid()
{
    delete ui;
}

void ScheduleWid::onItemClicked(QListWidgetItem *item) {
    TagList *widget = qobject_cast<TagList *>(ui->listWidget->itemWidget(item));
    if (widget) {
        QString path = widget->getFilePath();
        emit fileClicked(path);
    }
}

void ScheduleWid::loadTags() {
    ui->comboBox->clear();
    ui->comboBox->addItem("刷新");

    QStringList tags = dbservice.dbTags().getAllTags();
    for (const QString &tag : tags) {
        ui->comboBox->addItem(tag);
    }
}

void ScheduleWid::filterByTag(const QString &tag) {
    ui->listWidget->clear();
    QList<FilePathInfo> files = dbservice.dbTags().getFilePathsByTag(tag);

    for (const auto &info : files) {
        TagList *taglist = new TagList(info);

        QListWidgetItem *listItem = new QListWidgetItem(ui->listWidget);
        listItem->setSizeHint(taglist->sizeHint());
        ui->listWidget->addItem(listItem);
        ui->listWidget->setItemWidget(listItem, taglist);
    }
}


void ScheduleWid::onSearch(const QString &keyword) {
    ui->listWidget->clear();

    // 调用 modified searchFiles 方法，获取 FilePathInfo 结构体列表
    QList<FilePathInfo> files = dbservice.dbTags().searchFiles(keyword);

    // 遍历文件信息列表，创建 TagList 小部件
    for (const FilePathInfo &fileInfo : files) {
        TagList *widget = new TagList(fileInfo);  // 传递结构体数据到 TagList

        QListWidgetItem *listItem = new QListWidgetItem(ui->listWidget);
        listItem->setSizeHint(widget->sizeHint());
        ui->listWidget->addItem(listItem);
        ui->listWidget->setItemWidget(listItem, widget);
    }
}


void ScheduleWid::startExpirationCheck() {
    expirationTimer = new QTimer(this);
    connect(expirationTimer, &QTimer::timeout, this, &ScheduleWid::checkExpiration);
    expirationTimer->start(180000);  // 每30分钟（30 * 60 * 1000毫秒）
}

void ScheduleWid::checkExpiration() {
    QList<FilePathInfo> files = dbservice.dbTags().getFilePathsByTag("刷新");

    for (const auto &file : files) {
        QString path = file.filePath;
        QDateTime expDate = file.expirationDate;

        if (expDate.isValid() && QDateTime::currentDateTime().secsTo(expDate) <= 2 * 3600) {  // 2小时内到期
            int fileid = 0;
            QStringList tag;
            QString annotation;
            QVariantMap data;

            dbservice.dbTags().getFileId(path, fileid);
            dbservice.dbTags().getTags(fileid, tag);
            dbservice.dbTags().getAnnotation(fileid,annotation);

            data["tag"] = tag;
            data["annotation"] = annotation;
            manager->notify("到期提醒", path, data);  // 传递title, body和data

        }
    }
}


void ScheduleWid::on_sortBtn_clicked()
{
    ui->listWidget->clear();
    QList<FilePathInfo> files = dbservice.dbTags().getFilePathsByTag("刷新");
    std::sort(files.begin(), files.end(), [](const FilePathInfo &a, const FilePathInfo &b) {
        return a.expirationDate < b.expirationDate;
    });
    for (const FilePathInfo &file : files) {
        TagList *widget = new TagList(file);

        QListWidgetItem *listItem = new QListWidgetItem(ui->listWidget);
        listItem->setSizeHint(widget->sizeHint());
        ui->listWidget->addItem(listItem);
        ui->listWidget->setItemWidget(listItem, widget);
    }
}


void ScheduleWid::on_comboBox_currentIndexChanged(int index)
{
    QString tag = ui->comboBox->currentText();
    filterByTag(tag);
}

