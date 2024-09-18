#ifndef WFILETAG_H
#define WFILETAG_H

#include <QWidget>
#include <QFileSystemModel>
#include <QModelIndex>
#include "TagItemDelegate.h"
#include "../manager/DatabaseManager.h"

namespace Ui {
class WidgetRU;
}

class WidgetRU : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetRU(DatabaseManager *dbManager, QWidget *parent = nullptr);
    ~WidgetRU();

private slots:
    void onItemClicked(const QModelIndex &index);
    void goButtonClicked();
    void on_saveButton_clicked();
    void handleButtonClicked(const QModelIndex &index);

    void on_setReminderButton_clicked();

signals:
    void fileOpened(const QString &filePath);

private:
    void loadFileMetadata(const QString &filePath);
    void saveExpirationDate(const QString &filePath, const QDate &expirationDate);

    Ui::WidgetRU *ui;
    QFileSystemModel *fileSystemModel;
    TagItemDelegate *tagItemdelegate;
    DatabaseManager *dbManager;
    QString curfilePath;
    QString currentDir;
};

#endif // WFILETAG_H
