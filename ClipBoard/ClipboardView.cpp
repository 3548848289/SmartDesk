#include "ClipboardView.h"
#include "ui_ClipboardView.h"

ClipboardView::ClipboardView(QWidget *parent) : QWidget(parent),
    ui(new Ui::ClipboardView), dbservice(dbService::instance("./SmartDesk.db")){
    ui->setupUi(this);
    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->listWidget->setWordWrap(true);
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget->scrollToBottom();
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    clipboard = QGuiApplication::clipboard();

    connect(clipboard, &QClipboard::dataChanged, this, &ClipboardView::onClipboardChanged);
    setAcceptDrops(true);

    int hours = SettingManager::Instance().clip_board_hours();
    QList<QString> items = dbservice.dbClip().loadRecentHistory(hours);

    for (const QString &content : items)
        ui->listWidget->addItem(content);
    initialItemCount = ui->listWidget->count();
}

void ClipboardView::onClipboardChanged()
{
    const QMimeData *mimeData = clipboard->mimeData();
    if(mimeData->hasText()) {
        QString text = mimeData->text();
        if (!text.isEmpty()) {
            QListWidgetItem *item = new QListWidgetItem(text);
            item->setData(Qt::UserRole, text);  // 用于标记
            item->setToolTip(text);
            item->setTextAlignment(Qt::AlignTop);
            ui->listWidget->addItem(item);
        }
    }
}

void ClipboardView::copyItem()
{
    if (currentRightClickedItem)
        clipboard->setText(currentRightClickedItem->text());
}

void ClipboardView::deleteItem()
{
    QList<QListWidgetItem *> selectedItems = ui->listWidget->selectedItems();
    for (QListWidgetItem *item : selectedItems) {
        delete item;
    }
    currentRightClickedItem = nullptr;
}


ClipboardView::~ClipboardView()
{
    qDebug() << "保存记录";
    on_saveButton_clicked();

}

void ClipboardView::on_clearButton_clicked()
{
    ui->listWidget->clear();
}


void ClipboardView::on_saveButton_clicked()
{
    int successCount = 0;
    for (int i = initialItemCount; i < ui->listWidget->count(); ++i) {
        QString content = ui->listWidget->item(i)->text();
        if (dbservice.dbClip().setHistory(content))
            successCount++;
    }
}


void ClipboardView::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if (!item)
        return;
    QString data = item->data(Qt::UserRole).toString();
    clipboard->setText(data);
}


void ClipboardView::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    currentRightClickedItem = ui->listWidget->itemAt(pos);
    if (!currentRightClickedItem)
        return;

    QMenu menu(this);
    QAction *copyAction = menu.addAction("复制");
    QAction *deleteAction = menu.addAction("删除");

    connect(copyAction, &QAction::triggered, this, &ClipboardView::copyItem);
    connect(deleteAction, &QAction::triggered, this, &ClipboardView::deleteItem);

    menu.exec(ui->listWidget->mapToGlobal(pos));
}

