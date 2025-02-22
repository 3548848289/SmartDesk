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
        QMessageBox msgbox(QMessageBox::Information, QStringLiteral("具体信息"), data.value("title").toString());


        QStringList tagList = data.value("tag").toStringList();
        QString allDetails = data.value("body").toString() + "\n\n" +
                             "标签: " + tagList.join(", ") + "\n" +
                             "备注: " + data.value("annotation").toString() + "\n" +
                             "到期时间: " + data.value("expirationDate").toString();

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
    QList<FilePathInfo> files = dbservice.dbTags().searchFiles(keyword);
    for (const FilePathInfo &fileInfo : files) {
        TagList *widget = new TagList(fileInfo);

        QListWidgetItem *listItem = new QListWidgetItem(ui->listWidget);
        listItem->setSizeHint(widget->sizeHint());
        ui->listWidget->addItem(listItem);
        ui->listWidget->setItemWidget(listItem, widget);
    }
}


void ScheduleWid::startExpirationCheck() {
    expirationTimer = new QTimer(this);
    connect(expirationTimer, &QTimer::timeout, this, &ScheduleWid::checkExpiration);
    int reminderInterval = SettingManager::Instance().getReminderInterval();
    expirationTimer->start(reminderInterval);
}

void ScheduleWid::checkExpiration() {
    QList<FilePathInfo> files = dbservice.dbTags().getFilePathsByTag("刷新");

    QString reminderType = SettingManager::Instance().getReminderType();
    int reminderTime = SettingManager::Instance().getReminderTime();

    for (const auto &file : files) {
        QString path = file.filePath;
        QDateTime expDate = file.expirationDate;

        if (expDate.isValid() && QDateTime::currentDateTime().secsTo(expDate) <= reminderTime) {
            QVariantMap data;
            data["tag"] = file.tagName;
            data["annotation"] = file.annotation;
            data["expirationDate"] = file.expirationDate;

            if (reminderType == "弹窗提醒")
                manager->notify("到期提醒", path, data);
            else if (reminderType == "Email") {
                qDebug() << "邮件提醒";
                // manager->sendEmail("到期提醒", path, data);
            }
        }
    }
}

void ScheduleWid::on_comboBox_currentIndexChanged(int index)
{
    QString tag = ui->comboBox->currentText();
    filterByTag(tag);
}


void ScheduleWid::on_sortComboBox_currentIndexChanged(int index)
{
    if(index == 0 || index == 1)
    {
        ui->listWidget->clear();
        QList<FilePathInfo> files = dbservice.dbTags().getFilePathsByTag("刷新");

        bool isAscending = (index == 0);
        std::sort(files.begin(), files.end(), [isAscending](const FilePathInfo &a, const FilePathInfo &b) {
            return isAscending ? a.expirationDate < b.expirationDate : a.expirationDate > b.expirationDate;
        });


        for (const FilePathInfo &file : files) {
            TagList *widget = new TagList(file);

            QListWidgetItem *listItem = new QListWidgetItem(ui->listWidget);
            listItem->setSizeHint(widget->sizeHint());
            ui->listWidget->addItem(listItem);
            ui->listWidget->setItemWidget(listItem, widget);
        }
    }
}


