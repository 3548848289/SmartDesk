#include "include/TabHandleIMG.h"
#include <QHBoxLayout>

TabHandleIMG::TabHandleIMG(const QString& filePath, QWidget *parent)
    : TabAbstract(filePath, parent), angle(0), scaleValue(0.5), shearValue(0), translateValue(0)
{
    QSplitter* splitter = new QSplitter(Qt::Vertical, this);

    scene = new QGraphicsScene;
    scene->setSceneRect(-100, -100, 200, 200);

    QPixmap *pixmap = new QPixmap(filePath);
    pixItem = new PixItem(pixmap);
    scene->addItem(pixItem);
    pixItem->setPos(0, 0);

    view = new QGraphicsView;
    view->setScene(scene);
    view->setMinimumSize(200, 200);

    ControlFrame *controlFrame = new ControlFrame(this);

    splitter->addWidget(view);
    splitter->addWidget(controlFrame);

    splitter->setSizes({400, 100});

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(splitter);
    setLayout(layout);

    setWindowTitle(tr("Graphics Item Transformation"));
    showControlFrame(controlFrame);

    connect(controlFrame, &ControlFrame::textAdded, this, &TabHandleIMG::onTextAdded);
    connect(controlFrame, &ControlFrame::exportRequested, this, &TabHandleIMG::exportImage);

}


void TabHandleIMG::addTextToImage(const QString &text, const QPointF &position) {
    textItem = new QGraphicsTextItem(text);
    QFont font = textItem->font();  // 使用默认字体
    font.setPointSize(16);  // 设置字体大小
    textItem->setFont(font);
    textItem->setPos(position);
    scene->addItem(textItem);

}

void TabHandleIMG::onTextAdded(const QString &text, const QPointF &position) {
    // 在图像上添加文字，位置由用户指定
    addTextToImage(text, position);
}

void TabHandleIMG::showControlFrame(ControlFrame *controlFrame)
{
        connect(controlFrame, &ControlFrame::rotateChanged, this, [=](int value) {
            angle = value;
            updateTransformations(value, scaleValue, shearValue, translateValue);
        });
        connect(controlFrame, &ControlFrame::scaleChanged, this, [=](int value) {
            scaleValue = value / 10.0;
            updateTransformations(angle, scaleValue, shearValue, translateValue);
        });
        connect(controlFrame, &ControlFrame::shearChanged, this, [=](int value) {
            shearValue = value / 10.0;
            updateTransformations(angle, scaleValue, shearValue, translateValue);
        });
        connect(controlFrame, &ControlFrame::translateChanged, this, [=](int value) {
            translateValue = value;
            updateTransformations(angle, scaleValue, shearValue, translateValue);
        });
}

void TabHandleIMG::updateTransformations(int angle, qreal scale, qreal shear, qreal translate)
{
    view->resetTransform();
    view->rotate(angle);
    view->scale(scale, scale);
    view->shear(shear, 0);
    view->translate(translate, translate);
}

void TabHandleIMG::exportImage(const QString &filePath) {
    // 获取场景的边界，扩展到包含所有图形项
    QRectF sceneRect = scene->sceneRect();
    QRectF itemsRect = scene->itemsBoundingRect(); // 获取所有图形项的边界
    sceneRect = sceneRect.united(itemsRect);  // 合并场景区域和项的边界

    // 创建 QImage 来保存场景内容
    QImage image(sceneRect.width(), sceneRect.height(), QImage::Format_ARGB32);
    image.fill(Qt::white);  // 填充背景色为白色

    // 创建 QPainter 对象并设置渲染区域
    QPainter painter(&image);
    QTransform transform;
    transform.translate(-sceneRect.left(), -sceneRect.top());  // 平移到场景的起点
    painter.setTransform(transform);

    // 如果有视图，考虑视图的缩放比例
    if (!scene->views().isEmpty()) {
        QGraphicsView *view = scene->views().first();  // 获取第一个视图
        QTransform viewTransform = view->transform();
        painter.scale(viewTransform.m11(), viewTransform.m22());  // 按视图缩放渲染
    }

    // 渲染整个场景
    scene->render(&painter, QRectF(), sceneRect);

    // 保存图像
    if (!image.isNull()) {
        if (!image.save(filePath)) {
            QMessageBox::warning(this, tr("Export Error"), tr("Failed to export image."));
        } else {
            QMessageBox::information(this, tr("Export Success"), tr("Image successfully exported."));
        }
    } else {
        QMessageBox::warning(this, tr("Export Error"), tr("Image is not loaded or invalid."));
    }
}
