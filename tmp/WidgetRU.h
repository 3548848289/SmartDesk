#ifndef WIDGETRU_H
#define WIDGETRU_H

#include <QWidget>
#include <QTreeView>
#include <QFileSystemModel>

namespace Ui {
class WidgetRU;
}

class WidgetRU : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetRU(QWidget *parent = nullptr);
    ~WidgetRU();

private:
    Ui::WidgetRU *ui;

    QTreeView *treeView;
    QFileSystemModel *fileSystemModel;
};

#endif // WIDGETRU_H
