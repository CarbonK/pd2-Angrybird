#ifndef MEGUMI_H
#define MEGUMI_H

#include "bird.h"

#include <QGraphicsScene>
#include <QTimer>

class Megumi:
public Bird
{

    public:

        Megumi(b2World *dim, QPointF point, QGraphicsScene *scene, QTimer *timer);

        void feature();

};

#endif // MEGUMI_H
