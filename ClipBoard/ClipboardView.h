#ifndef CLIPBOARDVIEW_H
#define CLIPBOARDVIEW_H

#include <QWidget>
#include <QClipboard>
#include <QListWidgetItem>
#include <QMenu>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QStringList>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "../manager/include/dbService.h"
#include "../Setting/include/SettingManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ClipboardView; }
QT_END_NAMESPACE

class ClipboardView : public QWidget
{
    Q_OBJECT

public:
    explicit ClipboardView(QWidget *parent = nullptr);
    ~ClipboardView();

private slots:
    void onClipboardChanged();
    void copyItem();
    void deleteItem();

    void on_clearButton_clicked();
    void on_saveButton_clicked();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_customContextMenuRequested(const QPoint &pos);

private:
    Ui::ClipboardView *ui;
    QClipboard *clipboard;
    QListWidgetItem *currentRightClickedItem = nullptr;
    QStringList sessionNewItems;
    dbService& dbservice;
    int initialItemCount = 0;

};

#endif // CLIPBOARDVIEW_H


