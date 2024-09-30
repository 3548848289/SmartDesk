#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <QSlider>
#include <QLineEdit>
#include <QSettings>
#include <QDebug>
namespace Ui {
class Setting;
}

class Setting : public QWidget {
    Q_OBJECT
public:
    Setting(QWidget *parent = nullptr);
    ~Setting();

signals:
    void fontSizeChanged(int size);

private slots:
    void onFontSizeChanged(int value);
    void onLineEditEditingFinished();

private:
    void loadSettings();
    void saveSettings();
    void updateFontSize(int size);

    Ui::Setting *ui;
};




#endif // SETTING_H
