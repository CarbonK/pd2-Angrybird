#include "item.h"

#include <QDebug>

Item::Item(b2World *dim):
world(dim) , body(NULL) , exterior(NULL)
{}

Item::~Item(){

    world->DestroyBody(body);
    delete exterior;

}

QPair<float , float> Item::unit = QPair<float , float>();

void Item::setUnit(float meterX , float meterY , float pixelX , float pixelY){unit = QPair<float , float>(pixelX / meterX , pixelY / meterY);}

void Item::paint(){

    b2Vec2 pos = body->GetPosition();

    QPointF point;
    point.setX(pos.x * unit.first - size.width() / 2);
    point.setY(-(pos.y * unit.second - 600 + size.height() / 2));
    qDebug() << point.x() << ' ' << point.y();

    exterior->setPos(point);
    exterior->resetTransform();
    exterior->setRotation(-(body->GetAngle() * 180 / 3.1415926));

}
