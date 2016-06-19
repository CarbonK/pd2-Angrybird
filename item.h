#ifndef ITEM_H
#define ITEM_H

#include <Box2D/Box2D.h>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
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
        void setVelocity(float , float);
        void setDeathflag(bool);
        float getMass();
        b2Vec2 getVelocity();
        bool getDeathflag();
        b2Body * getBody();
        QGraphicsPixmapItem * getExterior();

        virtual void collision(Item *);

    protected:

        b2World *world;
        b2Body *body;
        QGraphicsPixmapItem *exterior;
        QSizeF size;
        static QPair<float , float> unit;
        const int windowH;
        bool Deathflag;

    signals:

        void explosion();

    public slots:

        void paint();

};

#endif // ITEM_H
