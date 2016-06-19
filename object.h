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

        Object(b2World *dim, QPointF point , int type, QGraphicsScene *scene, QTimer *timer, bool Pol = true , float HPscale = 1);
        ~Object();

        void collision(Item *);

        enum{P1X1 , P2X1 , P2X2 , P4X1 , P4X2 , P4X4 , P8X1 , P10X1 , CB , CS};

    private:

        float HP;
        float hpScale;
        QVector<QPixmap> image;

};

#endif // OBJECT_H
