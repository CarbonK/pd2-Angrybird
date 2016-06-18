#ifndef LAND_H
#define LAND_H

#include "item.h"

#include <QGraphicsScene>

class Land:
public Item
{

    public:

        explicit Land(b2World *dim, QRectF rect, QPixmap pix, QGraphicsScene *scene);
        ~Land();

};

#endif // LAND_H
