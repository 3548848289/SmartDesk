#pragma once
#include <QGraphicsTextItem>
#include <QMenu>
#include <QFontDialog>
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QFontDialog>
#include <QInputDialog>
#include <QLabel>
class WaterMark : public QGraphicsTextItem
{
public:
    WaterMark(const QString& text);

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;
};

