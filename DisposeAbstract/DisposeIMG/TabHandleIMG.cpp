#include "include/TabHandleIMG.h"
#include <QHBoxLayout>

TabHandleIMG::TabHandleIMG(const QString& filePath, QWidget *parent)
    : TabAbstract(filePath, parent), angle(0), scaleValue(0.5), shearValue(0), translateValue(0)
{
    QSplitter* splitter = new QSplitter(Qt::Vertical, this);

    scene = new QGraphicsScene;
    // scene->setSceneRect(-100, -100, 200, 200);

    QPixmap *pixmap = new QPixmap(filePath);
    pixItem = new PixItem(pixmap);
    scene->addItem(pixItem);
    scene->setSceneRect(pixItem->boundingRect());
    pixItem->setPos(0, 0);

    view = new QGraphicsView;
    view->setScene(scene);

    view->setMinimumSize(200, 200);
    view->installEventFilter(this);
    view->fitInView(pixItem, Qt::KeepAspectRatio);

    ControlFrame *controlFrame = new ControlFrame(this);
    splitter->addWidget(view);
    splitter->addWidget(controlFrame);

    splitter->setSizes({700, 100});

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(splitter);
    setLayout(layout);

    setWindowTitle(tr("Graphics Item Transformation"));
    showControlFrame(controlFrame);

    connect(controlFrame, &ControlFrame::textAdded, this, &TabHandleIMG::onTextAdded);
    connect(controlFrame, &ControlFrame::exportRequested, this, &TabHandleIMG::exportImage);

}

void TabHandleIMG::test()
{
    // controlFrame->show();
    qDebug() << "TabHandleCSV: Showing control frame!";
}

void TabHandleIMG::onTextAdded(const QString &text, const QPointF &position) {
    addTextToImage(text, position);
}



void TabHandleIMG::showControlFrame(ControlFrame *controlFrame)
{
        connect(controlFrame, &ControlFrame::rotateChanged, this, [=](int value) {
            angle = value;
            updateTransformations(value, scaleValue, shearValue, translateValue);
        });
        connect(controlFrame, &ControlFrame::scaleChanged, this, [=](int value) {
            scaleValue = value / 50.0;
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

void TabHandleIMG::addTextToImage(const QString &text, const QPointF &position) {
    // 获取当前视图的变换矩阵
    QTransform currentTransform = view->transform();

    // 转换坐标为当前变换下的坐标
    QPointF transformedPos = currentTransform.inverted().map(position);

    // 创建文字项
    textItem = new QGraphicsTextItem(text);
    QFont font = textItem->font();
    font.setPointSize(16);
    textItem->setFont(font);
    textItem->setPos(transformedPos);
    scene->addItem(textItem);
}

bool TabHandleIMG::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == view && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            QPointF scenePos = view->mapToScene(mouseEvent->pos());
            bool ok;
            QString text = QInputDialog::getText(
                this, tr("输入文字"), tr("请输入水印文字:"), QLineEdit::Normal, "", &ok);
            if (ok && !text.isEmpty())
                addTextToImage(text, scenePos);
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}


void TabHandleIMG::exportImage(const QString &filePath) {
    if (!scene) return;

    QRectF sceneRect = scene->itemsBoundingRect(); // 获取所有图元的边界
    QImage image(sceneRect.size().toSize(), QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::white); // 白色背景（你可以换成透明：Qt::transparent）

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // 应用 scene 坐标系的偏移
    painter.translate(-sceneRect.topLeft());

    scene->render(&painter);
    painter.end();

    if (!image.save(filePath)) {
        QMessageBox::warning(this, tr("保存失败"), tr("无法保存图像到路径: %1").arg(filePath));
    } else {
        QMessageBox::information(this, tr("保存成功"), tr("图像已保存到: %1").arg(filePath));
    }

}


