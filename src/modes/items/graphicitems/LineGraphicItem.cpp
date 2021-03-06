#include "LineGraphicItem.h"

LineGraphicItem::LineGraphicItem(AbstractItem* parent, qreal x, qreal y)
    : AbstractGraphicItem(parent),
      QGraphicsLineItem(x, y, x, y) {
}

void LineGraphicItem::mousePressEvent(QGraphicsSceneMouseEvent* e) {
    AbstractGraphicItem::mousePressEvent(e);
    QGraphicsLineItem::mousePressEvent(e);
}

void LineGraphicItem::mouseMoveEvent(QGraphicsSceneMouseEvent* e) {
    AbstractGraphicItem::mouseMoveEvent(e);
}

void LineGraphicItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* e) {
    AbstractGraphicItem::mouseReleaseEvent(e);
    QGraphicsLineItem::mouseReleaseEvent(e);
}

void LineGraphicItem::hoverEnterEvent(QGraphicsSceneHoverEvent* e) {
    AbstractGraphicItem::hoverEnterEvent(e);
    QGraphicsLineItem::hoverEnterEvent(e);
}

void LineGraphicItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* e) {
    AbstractGraphicItem::hoverLeaveEvent(e);
    QGraphicsLineItem::hoverLeaveEvent(e);
}
