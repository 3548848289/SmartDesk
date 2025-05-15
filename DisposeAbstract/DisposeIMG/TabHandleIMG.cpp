#include "include/TabHandleIMG.h"
#include "include/WaterMark.h"
#include <QHBoxLayout>
#include <QtSvgWidgets/QGraphicsSvgItem>
#include <QtSvg/QSvgRenderer>

TabHandleIMG::TabHandleIMG(const QString& filePath, QWidget *parent)
    : TabAbstract(filePath, parent), angle(0), scaleValue(0.5), shearValue(0), translateValue(0)
{
    QSplitter* splitter = new QSplitter(Qt::Vertical, this);
    scene = new QGraphicsScene;
    view = new QGraphicsView;
    view->setScene(scene);
    view->setMinimumSize(200, 200);
    view->installEventFilter(this);

    controlFrame = new ControlFrame(this);
    splitter->addWidget(view);
    splitter->addWidget(controlFrame);
    splitter->setSizes({700, 100});

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(splitter);
    setLayout(layout);

    setWindowTitle(tr("Graphics Item Transformation"));
    showControlFrame(controlFrame);

    setContentModified(false);

    connect(controlFrame, &ControlFrame::textAdded, this, &TabHandleIMG::onTextAdded);
    connect(controlFrame, &ControlFrame::exportRequested, this, &TabHandleIMG::exportImage);
}



void TabHandleIMG::loadFromFile(const QString &fileName)
{
    scene->clear();  // 每次都清空，防止图像叠加

    QFileInfo fileInfo(fileName);
    QString suffix = fileInfo.suffix().toLower();

    if (suffix == "svg") {
        QGraphicsSvgItem* svgItem = new QGraphicsSvgItem(fileName);
        if (!svgItem->renderer()->isValid()) {
            QMessageBox::warning(this, tr("加载错误"), tr("SVG 文件无法打开: %1").arg(fileName));
            delete svgItem;
            return;
        }

        scene->addItem(svgItem);
        scene->setSceneRect(svgItem->boundingRect());
        svgItem->setPos(0, 0);
        view->fitInView(svgItem, Qt::KeepAspectRatio);
    } else {
        QPixmap* pixmap = new QPixmap(fileName);
        if (pixmap->isNull()) {
            QMessageBox::warning(this, tr("加载错误"), tr("%1 文件无法打开").arg(fileName));
            delete pixmap;
            return;
        }

        pixItem = new PixItem(pixmap);
        scene->addItem(pixItem);
        scene->setSceneRect(pixItem->boundingRect());
        pixItem->setPos(0, 0);
        view->fitInView(pixItem, Qt::KeepAspectRatio);
    }
}


void TabHandleIMG::saveToFile(const QString &fileName) {
    exportImage(fileName);
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

// void TabHandleIMG::updateTransformations(int angle, qreal scale, qreal shear, qreal translate)
// {
//     QTransform transform;
//     transform.translate(translate, translate);
//     transform.shear(shear, 0);
//     transform.scale(scale, scale);
//     transform.rotate(angle);

//     if (pixItem)
//         pixItem->setTransform(transform);
// }


void TabHandleIMG::addTextToImage(const QString &text, const QPointF &position) {
    WaterMark* textItem = new WaterMark(text);
    QPointF offset(0, -12);
    textItem->setFont(QFont("Arial", 12));

    textItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    textItem->setPos(position + offset);
    scene->addItem(textItem);

    setContentModified(true);
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
    QRectF sceneRect = scene->itemsBoundingRect();
    QRect imageRect = sceneRect.toAlignedRect();
    QImage image(imageRect.size(), QImage::Format_ARGB32);
    image.fill(Qt::white);

    // 将 scene 渲染到 QImage
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(-sceneRect.topLeft());
    scene->render(&painter);
    painter.end();

    if (!image.save(filePath)) {
        QMessageBox::warning(this, tr("保存失败"), tr("无法保存图像到 %1").arg(filePath));
    }
    setContentModified(false);
}
