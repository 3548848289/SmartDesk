#pragma once
#include <QGraphicsTextItem>
#include <QMenu>
#include <QFontDialog>

class WaterMark : public QGraphicsTextItem
{
public:
    WaterMark(const QString& text);

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;
};

