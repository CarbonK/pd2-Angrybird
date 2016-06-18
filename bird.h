#ifndef BIRD_H
#define BIRD_H

#include "item.h"

#include <QGraphicsScene>
#include <QTimer>

#define B_DENSITY 100.0f
#define B_FRACTION 10.0f
#define B_RESTITUTION 0.3f

class Bird:
public Item
{

    public:

        Bird(b2World *dim, float x, float y, float r, QPixmap pix, QGraphicsScene *scene , QTimer *timer);
        ~Bird();

        void setGscale(float scale);

        virtual void feature();

};

#endif // BIRD_H
