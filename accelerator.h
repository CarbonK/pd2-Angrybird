#ifndef ACCELERATOR_H
#define ACCELERATOR_H

#include "bird.h"

#include <QGraphicsScene>
#include <QTimer>

class Accelerator:
public Bird
{

    public:

        Accelerator(b2World *dim, float x, float y, QGraphicsScene *scene, QTimer *timer);

        void feature();

};

#endif // ACCELERATOR_H
