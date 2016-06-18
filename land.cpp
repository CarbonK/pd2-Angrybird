#include "land.h"

#include <new>
#include <QDebug>

Land::Land(b2World *dim , QRectF rect , QPixmap pix , QGraphicsScene *scene):
Item(dim)
{

    b2BodyDef def;
    def.position.Set((rect.x() + rect.width() / 2) * unit.first , 0);
    def.type = b2_staticBody;
    def.userData = this;

    b2PolygonShape shape;
    shape.SetAsBox(rect.width() / 2 * unit.first , rect.height() / 2 * unit.second);

    body = world->CreateBody(&def);
    body->CreateFixture(&shape , 0);

    exterior = new QGraphicsPixmapItem(pix);

    scene->addItem(exterior);

    exterior->setPos(rect.x() , rect.y());
    exterior->resetTransform();
    exterior->setRotation(-(body->GetAngle() * 180 / 3.1415926));

}

Land::~Land(){}
