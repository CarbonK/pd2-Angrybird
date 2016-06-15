#ifndef BIRD_H
#define BIRD_H

#include "item.h"

#include <QGraphicsScene>
#include <QTimer>

#define B_DENSITY 10.0f
#define B_FRACTION 0.2f
#define B_RESTITUTION 0.4f

class Bird:
public Item
{

    public:

        Bird(b2World *dim, float x, float y, float r, QPixmap pix, QGraphicsScene *scene);

};

#endif // BIRD_H
