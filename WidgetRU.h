

#ifndef WIDGETRU_H
#define WIDGETRU_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QWidget>
#include <QTreeView>
#include <QFileSystemModel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QModelIndex>

#include "TagItemDelegate.h"

namespace Ui {
    class WidgetRU;
}

class WidgetRU : public QWidget
{
    Q_OBJECT

public:
    void handleButtonClicked(const QModelIndex &index);

    explicit WidgetRU(QWidget *parent = nullptr);
    ~WidgetRU();

protected:

signals:
    void fileOpened(const QString &filePath);

private slots:
    void onItemClicked(const QModelIndex &index);
    void saveMetadata(const QString &filePath, const QStringList &tags, const QString &annotation);
    void getFileMetadata(const QString &filePath, QStringList &tags, QString &annotation);

    void goButtonClicked();

    void on_saveButton_clicked();

    void on_newButton_clicked();


private:

    QString curfilePath;
    QString currentDir;

    Ui::WidgetRU *ui;
    QFileSystemModel *fileSystemModel;
    TagItemDelegate * tagItemdelegate;

};

#endif // WIDGETRU_H


