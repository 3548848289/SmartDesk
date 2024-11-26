#include "TabHandleIMG.h"
#include <QHBoxLayout>

TabHandleIMG::TabHandleIMG(const QString& filePath, QWidget *parent)
    : TabAbstract(filePath, parent), angle(0), scaleValue(1), shearValue(0), translateValue(0)
{
    scene = new QGraphicsScene;
    scene->setSceneRect(-200, -200, 400, 400);

    QPixmap *pixmap = new QPixmap(filePath);
    pixItem = new PixItem(pixmap);
    scene->addItem(pixItem);
    pixItem->setPos(0, 0);

    view = new QGraphicsView;
    view->setScene(scene);
    view->setMinimumSize(400, 400);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(20);
    mainLayout->addWidget(view);
    setLayout(mainLayout);
    setWindowTitle(tr("Graphics Item Transformation"));
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
