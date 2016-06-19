#ifndef PIGGIE_H
#define PIGGIE_H

#include "item.h"

#include <QGraphicsScene>
#include <QTimer>
#include <QVector>

#define P_DENSITY 50.0f
#define P_FRACTION 10.0f
#define P_RESTITUTION 0.2f

class Piggie:
public Item
{

    public:

        Piggie(b2World *dim, QPointF point, int t , QGraphicsScene *scene, QTimer *timer);

        void collision(Item *);

        enum{small , medium , helmet , king};

    private:

        float HP;
        QVector<QPixmap> image;

};

#endif // PIGGIE_H
