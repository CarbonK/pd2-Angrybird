#ifndef OBJECT_H
#define OBJECT_H

#include "item.h"

#include <QGraphicsScene>
#include <QTimer>
#include <QVector>

#define O_DENSITY 20.0f
#define O_FRACTION 10.0f
#define O_RESTITUTION 0.2f

class Object:
public Item
{

    public:

        Object(b2World *dim, QRectF rect, QPixmap pix, QGraphicsScene *scene, QTimer *timer, bool Pol = true , float HPscale = 1);
        ~Object();

        void collision(Item *);

    private:

        float HP;
        QVector<QPixmap> image;

};

#endif // OBJECT_H
