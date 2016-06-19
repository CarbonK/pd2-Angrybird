#ifndef BOMBER_H
#define BOMBER_H

#include "bird.h"

#include <QGraphicsScene>
#include <QTimer>

class Bomber:
public Bird
{

    public:

        Bomber(b2World *dim, QPointF point, QGraphicsScene *scene, QTimer *timer);

        void feature();

};

#endif // BOMBER_H
