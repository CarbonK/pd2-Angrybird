#include "land.h"

#include <new>

Land::Land(b2World *dim , QRectF rect , QPixmap pix , QGraphicsScene *scene):
Item(dim)
{

    b2BodyDef def;
    def.position.Set((rect.x() + rect.width() / 2) / unit.first , (600 - rect.y() - rect.height() / 2) / unit.second);
    def.type = b2_staticBody;
    def.userData = this;

    b2PolygonShape shape;
    shape.SetAsBox(rect.width() / unit.first , rect.height() / unit.second);

    body = dim->CreateBody(&def);
    body->CreateFixture(&shape , 0);

    size = QSizeF(rect.width() , rect.height());

    exterior = new QGraphicsPixmapItem(pix);

    scene->addItem(exterior);

    paint();

}
