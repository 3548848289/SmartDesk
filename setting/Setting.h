#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <QSlider>
#include <QLineEdit>
#include <QSettings>
#include <QDebug>
#include <QTreeWidgetItem>
#include <QCloseEvent>

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

private slots:
    void on_pushButton_clicked();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::Setting *ui;
    QSettings settings;
    void loadSettings();
    void saveSettings();

    void closeEvent(QCloseEvent *event);
};



#endif // SETTING_H
