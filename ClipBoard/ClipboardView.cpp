#include "ClipboardView.h"
#include "ui_ClipboardView.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

void ClipboardView::simulatePaste()
{
#ifdef Q_OS_WIN
    // 模拟 Ctrl+V 粘贴操作
    keybd_event(VK_CONTROL, 0, 0, 0); // 按下 Ctrl
    keybd_event('V', 0, 0, 0);        // 按下 V
    keybd_event('V', 0, KEYEVENTF_KEYUP, 0);  // 松开 V
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // 松开 Ctrl
#endif
}

ClipboardView::ClipboardView(QWidget *parent)
    : QWidget(parent), ui(new Ui::ClipboardView)
{
    ui->setupUi(this);
    ui->listWidget->setWordWrap(true);
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    clipboard = QGuiApplication::clipboard();

    connect(clipboard, &QClipboard::dataChanged, this, &ClipboardView::onClipboardChanged);
    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &ClipboardView::onItemDoubleClicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &ClipboardView::onClearButtonClicked);
    connect(ui->saveButton, &QPushButton::clicked, this, &ClipboardView::onSaveButtonClicked);

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, &QListWidget::customContextMenuRequested,
            this, &ClipboardView::showContextMenu);

    setAcceptDrops(true);
    onClipboardChanged();

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

            // 设置为多行显示
            item->setTextAlignment(Qt::AlignTop);

            // 添加到 QListWidget
            ui->listWidget->addItem(item);
        }
    }

    // 设置 QListWidget 的样式表
    ui->listWidget->setStyleSheet("QListWidget::item {"
                                  "   border: 1px solid lightgray;"
                                  "   padding: 5px;"
                                  "   margin: 2px;"
                                  "}"
                                  "QListWidget::item:selected {"
                                  "   background-color: #a8c5f7;"   // 选中项背景色
                                  "   color: black;"                 // 选中项文本颜色
                                  "}"
                                  "QListWidget::item:hover {"
                                  "   background-color: #e0e0e0;"   // 悬停项背景色
                                  "}");

    ui->listWidget->scrollToBottom();
}


void ClipboardView::onItemDoubleClicked(QListWidgetItem *item)
{
    if (!item) return;
    QString data = item->data(Qt::UserRole).toString();
    clipboard->setText(data);
}


void ClipboardView::onClearButtonClicked()
{
    ui->listWidget->clear();
}

void ClipboardView::onSaveButtonClicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "保存剪贴板历史", "", "Text Files (*.txt)");
    if (!filename.isEmpty()) {
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for (int i = 0; i < ui->listWidget->count(); ++i) {
                out << ui->listWidget->item(i)->text() << "\n";
            }
            file.close();
            QMessageBox::information(this, "保存成功", "剪贴板内容已保存！");
        } else {
            QMessageBox::warning(this, "保存失败", "无法写入文件！");
        }
    }
}

void ClipboardView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasText() || event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}


void ClipboardView::showContextMenu(const QPoint &pos)
{
    currentRightClickedItem = ui->listWidget->itemAt(pos);
    if (!currentRightClickedItem) return;

    QMenu menu(this);
    QAction *copyAction = menu.addAction("复制");
    QAction *deleteAction = menu.addAction("删除");

    connect(copyAction, &QAction::triggered, this, &ClipboardView::copyItem);
    connect(deleteAction, &QAction::triggered, this, &ClipboardView::deleteItem);

    menu.exec(ui->listWidget->mapToGlobal(pos));
}

void ClipboardView::copyItem()
{
    if (currentRightClickedItem) {
        clipboard->setText(currentRightClickedItem->text());
    }
}

void ClipboardView::deleteItem()
{
    if (currentRightClickedItem) {
        delete currentRightClickedItem;
        currentRightClickedItem = nullptr;
    }
}

ClipboardView::~ClipboardView()
{
    delete ui;
}
