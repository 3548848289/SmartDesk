#ifndef CLIPBOARDVIEW_H
#define CLIPBOARDVIEW_H

#include <QWidget>
#include <QClipboard>
#include <QListWidgetItem>
#include <QMenu>
#include <QMimeData>
#include <QDragEnterEvent>
#ifdef Q_OS_WIN
#include <windows.h>
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class ClipboardView; }
QT_END_NAMESPACE

class ClipboardView : public QWidget
{
    Q_OBJECT

public:
    explicit ClipboardView(QWidget *parent = nullptr);
    ~ClipboardView();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
private slots:
    void onClipboardChanged();
    void onItemDoubleClicked(QListWidgetItem *item);
    void onClearButtonClicked();
    void onSaveButtonClicked();
    void showContextMenu(const QPoint &pos);
    void copyItem();
    void deleteItem();

private:
    Ui::ClipboardView *ui;
    QClipboard *clipboard;
    QListWidgetItem *currentRightClickedItem = nullptr;  // For context menu
    void simulatePaste();
};

#endif // CLIPBOARDVIEW_H


