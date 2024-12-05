#include "TabHandleIMG.h"
#include <QHBoxLayout>

TabHandleIMG::TabHandleIMG(const QString& filePath, QWidget *parent)
    : TabAbstract(filePath, parent), angle(0), scaleValue(1), shearValue(0), translateValue(0)
{
    // 创建 QSplitter 实例
    QSplitter* splitter = new QSplitter(Qt::Vertical, this);  // 使用垂直方向的 QSplitter

    // 创建 QGraphicsView
    scene = new QGraphicsScene;
    scene->setSceneRect(-200, -200, 400, 400);

    QPixmap *pixmap = new QPixmap(filePath);
    pixItem = new PixItem(pixmap);
    scene->addItem(pixItem);
    pixItem->setPos(0, 0);

    view = new QGraphicsView;
    view->setScene(scene);
    view->setMinimumSize(400, 400);

    // 创建 controlFrame（假设是一个 QWidget 或其他控件）
    ControlFrame *controlFrame = new ControlFrame(this);  // 这里你可以替换为实际的控件类型

    // 将 QGraphicsView 和 controlFrame 添加到 QSplitter
    splitter->addWidget(view);
    splitter->addWidget(controlFrame);

    // 设置 QSplitter 中控件的初始大小比例
    splitter->setSizes({400, 100});  // 假设上面的图像部分占 400px，下面的控制框占 100px

    // 创建主布局，将 QSplitter 放入其中
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(splitter);  // 将 QSplitter 添加到布局中

    // 设置主布局
    setLayout(layout);

    // 设置窗口的标题
    setWindowTitle(tr("Graphics Item Transformation"));

    showControlFrame(controlFrame);
}

void TabHandleIMG::showControlFrame(ControlFrame *controlFrame)
{
    if (controlFrame) {
        controlFrame->setVisible(true); // 显示 ControlFrame
        controlFrame->setEnabled(true);

        // 连接信号
        connect(controlFrame, &ControlFrame::rotateChanged, this, [=](int value) {
            updateTransformations(value, scaleValue, shearValue, translateValue);
        });
        connect(controlFrame, &ControlFrame::scaleChanged, this, [=](int value) {
            scaleValue = value / 10.0; // 适当调整缩放比例
            updateTransformations(angle, scaleValue, shearValue, translateValue);
        });
        connect(controlFrame, &ControlFrame::shearChanged, this, [=](int value) {
            shearValue = value / 10.0; // 适当调整切变比例
            updateTransformations(angle, scaleValue, shearValue, translateValue);
        });
        connect(controlFrame, &ControlFrame::translateChanged, this, [=](int value) {
            translateValue = value; // 直接使用位移值
            updateTransformations(angle, scaleValue, shearValue, translateValue);
        });
    }
}

void TabHandleIMG::updateTransformations(int angle, qreal scale, qreal shear, qreal translate)
{
    view->resetTransform();
    view->rotate(angle);
    view->scale(scale, scale);
    view->shear(shear, 0);
    view->translate(translate, translate);
}

// 其他方法的实现...
