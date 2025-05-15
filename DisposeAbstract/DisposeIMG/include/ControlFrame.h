#ifndef CONTROLFRAME_H
#define CONTROLFRAME_H

#include <QWidget>
#include <QSlider>
#include <QGroupBox>
#include <QFileDialog>
#include "../../Setting/include/SettingManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ControlFrame; }
QT_END_NAMESPACE

class ControlFrame : public QWidget
{
    Q_OBJECT

public:
    ControlFrame(QWidget *parent = nullptr);
    ~ControlFrame();  // 需要定义析构函数来清理 UI

signals:
    void rotateChanged(int value);
    void scaleChanged(int value);
    void shearChanged(int value);
    void translateChanged(int value);
    void textAdded(const QString &text, const QPointF &position);
    void exportRequested(const QString &filePath);
private slots:

    void on_exportButton_clicked();

private:
    void setupConnections();  // 用于连接控件和信号槽

    Ui::ControlFrame *ui;  // UI 类的实例
};

#endif // CONTROLFRAME_H
