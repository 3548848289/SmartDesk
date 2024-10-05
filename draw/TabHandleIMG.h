#ifndef TABHANDLEIMG_H
#define TABHANDLEIMG_H

#include "../main/include/TabAbstract.h"
#include "PixItem.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QLabel>
#include "ControlFrame.h"
class TabHandleIMG : public TabAbstract
{
    Q_OBJECT

public:
    explicit TabHandleIMG(const QString& filePath, QWidget *parent = nullptr);

    void setText(const QString &text) override {}
    QString getText() const override {}
    void loadFromFile(const QString &fileName) override {}
    void saveToFile(const QString &fileName) {}
    void loadFromContent(const QByteArray &content) override {}
    void ReadfromServer(const QJsonObject& jsonObj) override {}
    void ChickfromServer(const QJsonObject& jsonObj) override {}
    void clearfromServer(const QJsonObject& jsonObj) override {}
    void editedfromServer(const QJsonObject& jsonObj) override {}

public slots:
    void showControlFrame(ControlFrame *controlFrame);

private:
    void updateTransformations(int angle, qreal scale, qreal shear, qreal translate);

    QLabel *imageLabel;
    QPixmap currentImage;

    QGraphicsView *view;
    QGraphicsScene *scene;
    PixItem *pixItem;

    int angle;
    qreal scaleValue;
    qreal shearValue;
    qreal translateValue;
};

#endif // TABHANDLEIMG_H
