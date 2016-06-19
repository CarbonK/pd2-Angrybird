#ifndef LV0_H
#define LV0_H

#include "bird.h"

#include <QGraphicsScene>
#include <QTimer>

class LV0:
public Bird
{

    public:

        LV0(b2World *dim, QPointF point, QGraphicsScene *scene, QTimer *timer);

};

#endif // LV0_H
