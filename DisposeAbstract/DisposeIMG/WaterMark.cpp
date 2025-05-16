#include "include/WaterMark.h"

WaterMark::WaterMark(const QString& text) : QGraphicsTextItem(text)
{
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
}

void WaterMark::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    QMenu menu;
    QAction* deleteAct = menu.addAction("删除");
    QAction* editFontAct = menu.addAction("更改样式");
    QAction* editSize = menu.addAction("更改字体大小");
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
    } else if (selected == editSize) {
        bool ok;
        int pointSize = QInputDialog::getInt(nullptr, "设置字体大小", "字号（建议10-200）:", 72, 1, 500, 1, &ok);
        if (ok) {
            QFont font = this->font();
            font.setPointSize(pointSize);
            this->setFont(font);
        }
    }


}
