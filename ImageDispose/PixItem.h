#ifndef PIXITEM_H
#define PIXITEM_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>

class PixItem : public QGraphicsItem
{
public:
    PixItem(QPixmap *pixmap);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPixmap getpixmap();
    void setPixmap(QPixmap pixmap);
    void updatePixmap(const QPixmap &newPixmap);  // 添加更新 QPixmap 的方法
private:
    QPixmap pix;  // 作为图元显示的图片
};

#endif // PIXITEM_H
