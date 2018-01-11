#ifndef SCREENSHOTGUN_LINEITEM_H
#define SCREENSHOTGUN_LINEITEM_H

#include <QGraphicsLineItem>
#include "AbstractItem.h"

class LineItem : public QGraphicsLineItem, public AbstractItem {

public:
    LineItem(Overlay&, qreal x, qreal y);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

    void hoverEnterEvent(QGraphicsSceneHoverEvent*);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*);
};

#endif //SCREENSHOTGUN_LINEITEM_H
