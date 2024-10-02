#ifndef CONTROLFRAME_H
#define CONTROLFRAME_H

#include <QFrame>
#include <QSlider>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

class ControlFrame : public QFrame
{
    Q_OBJECT

public:
    ControlFrame(QWidget *parent = nullptr);

signals:
    void rotateChanged(int value);
    void scaleChanged(int value);
    void shearChanged(int value);
    void translateChanged(int value);

private:
    void createControlFrame();
};

#endif // CONTROLFRAME_H
