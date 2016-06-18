#include "item.h"

#include <QDebug>

Item::Item(b2World *dim):
world(dim) , body(NULL) , exterior(NULL) , windowH(720) , Deathflag(false)
{}

Item::~Item(){}

QPair<float , float> Item::unit = QPair<float , float>();

void Item::setUnit(float meterX , float meterY , float pixelX , float pixelY){unit = QPair<float , float>(meterX / pixelX , meterY / pixelY);}

void Item::setVelocity(float x , float y){body->SetLinearVelocity(b2Vec2(x , y));}

float Item::getMass(){return body->GetMass();}

b2Vec2 Item::getVelocity(){return body->GetLinearVelocity();}

bool Item::getDeathflag(){return Deathflag;}

b2Body *Item::getBody(){return body;}

QGraphicsPixmapItem *Item::getExterior(){return exterior;}

void Item::collision(Item *){}

void Item::paint(){

    b2Vec2 pos = body->GetPosition();

    QPointF point;
    point.setX(pos.x / unit.first - size.width() / 2);
    point.setY(-(pos.y / unit.second - windowH + size.height() / 2));

    exterior->setPos(point);
    exterior->resetTransform();
    exterior->setRotation(-(body->GetAngle() * 180 / 3.1415926));

}
