#include "include/PixItem.h"

PixItem::PixItem(QPixmap *pixmap) : pix(*pixmap) {}

QRectF PixItem::boundingRect() const {
    return QRectF(0, 0, pix.width(), pix.height());
}

void PixItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->drawPixmap(0, 0, pix);
}


QPixmap PixItem::getpixmap()
{
    return pix;
}

void PixItem::setPixmap(QPixmap pixmap)
{
    pix = pixmap;
}

// PixItem.cpp

void PixItem::updatePixmap(const QPixmap &newPixmap) {
    pix = newPixmap;
    update();
}

