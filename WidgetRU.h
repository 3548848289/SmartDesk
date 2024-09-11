#ifndef WIDGETRU_H
#define WIDGETRU_H

#include <QWidget>
#include <QTreeView>
#include <QFileSystemModel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>


namespace Ui {
    class WidgetRU;
}

class WidgetRU : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetRU(QWidget *parent = nullptr);
    ~WidgetRU();

signals:
    void fileOpened(const QString &filePath);

private slots:
    void onItemClicked(const QModelIndex &index);
    void goButtonClicked();

private:
    Ui::WidgetRU *ui;
    QFileSystemModel *fileSystemModel;
};

#endif // WIDGETRU_H
