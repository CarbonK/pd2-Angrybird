#include "bird.h"

#include <QDebug>

Bird::Bird(b2World *dim , float x , float y , float r , QPixmap pix , QGraphicsScene *scene):
Item(dim)
{

    b2BodyDef def;
    def.position.Set((x + r) / unit.first , (600 - y - r) / unit.second);
    def.type = b2_dynamicBody;
    def.userData = this;

    b2CircleShape shape;
    shape.m_radius = r / (unit.first + unit.second) * 2;

    b2FixtureDef fixture;
    fixture.density = B_DENSITY;
    fixture.friction = B_FRACTION;
    fixture.restitution = B_RESTITUTION;
    fixture.shape = &shape;

    body = world->CreateBody(&def);
    body->CreateFixture(&fixture);

    size = QSizeF(r * 2 , r * 2);

    exterior = new QGraphicsPixmapItem(pix);

    scene->addItem(exterior);

    paint();

}
