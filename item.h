#ifndef ITEM_H
#define ITEM_H

#include <Box2D/Box2D.h>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPair>

class Item:
public QObject
{

    Q_OBJECT

    public:

        explicit Item(b2World *);
        ~Item();

        static void setUnit(float , float , float , float);

    protected:

        b2World *world;
        b2Body *body;
        QGraphicsPixmapItem *exterior;
        QSizeF size;
        static QPair<float , float> unit;

    public slots:

        void paint();

};

#endif // ITEM_H
