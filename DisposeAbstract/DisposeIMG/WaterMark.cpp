#include "include/WaterMark.h"
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QFontDialog>

WaterMark::WaterMark(const QString& text)
    : QGraphicsTextItem(text)
{
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
}

void WaterMark::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    QMenu menu;
    QAction* deleteAct = menu.addAction("删除");
    QAction* editFontAct = menu.addAction("更改字体大小");

    QAction* selected = menu.exec(event->screenPos());
    if (selected == deleteAct) {
        if (scene()) {
            scene()->removeItem(this);
            delete this;
        }
    } else if (selected == editFontAct) {
        QFont font = this->font();
        bool ok;
        QFont newFont = QFontDialog::getFont(&ok, font);
        if (ok) {
            setFont(newFont);
        }
    }
}
