#ifndef TABHANDLEIMG_H
#define TABHANDLEIMG_H

#include "../../main/include/TabAbstract.h"
#include "PixItem.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QLabel>
#include <QSplitter>
#include "ControlFrame.h"
class TabHandleIMG : public TabAbstract
{
    Q_OBJECT

public:
    explicit TabHandleIMG(const QString& filePath, QWidget *parent = nullptr);

    void setText(const QString &text) override {}
    QString getText() const override {  return " "; }
    void loadFromFile(const QString &fileName) override {}
    void saveToFile(const QString &fileName) {}
    void loadFromContent(const QByteArray &content) override {}
    void ReadfromServer(const QJsonObject& jsonObj) override {}
    void ChickfromServer(const QJsonObject& jsonObj) override {}
    void clearfromServer(const QJsonObject& jsonObj) override {}
    void editedfromServer(const QJsonObject& jsonObj) override {}

    void ControlWidget(QWidget* WControl){
        qDebug() << "TabHandleIMG: Showing control frame!";
    }

public slots:
    void showControlFrame(ControlFrame *controlFrame);
    void onTextAdded(const QString &text, const QPointF &position);

private:
    void updateTransformations(int angle, qreal scale, qreal shear, qreal translate);
    void addTextToImage(const QString &text, const QPointF &position);
    void exportImage(const QString &filePath);


    QGraphicsView *view;
    QGraphicsScene *scene;
    PixItem *pixItem;
    QGraphicsTextItem *textItem;

    ControlFrame *controlFrame;
    int angle;
    qreal scaleValue;
    qreal shearValue;
    qreal translateValue;
};

#endif // TABHANDLEIMG_H
