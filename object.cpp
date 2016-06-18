#include "object.h"

#include <QDebug>
#include <QtMath>

Object::Object(b2World *dim , QRectF rect , /*int type*/QPixmap pix , QGraphicsScene *scene , QTimer *timer , bool Pol , float HPscale):
Item(dim)
{

    b2BodyDef def;
    def.position.Set((rect.x() + rect.width() / 2) * unit.first , (windowH - rect.y() - rect.height() / 2) * unit.second);
    def.type = b2_dynamicBody;
    def.userData = this;

    b2PolygonShape Pshape;
    b2CircleShape Cshape;

    b2FixtureDef fixture;
    fixture.density = O_DENSITY;
    fixture.friction = O_FRACTION;
    fixture.restitution = O_RESTITUTION;

    if(Pol){

        Pshape.SetAsBox(rect.width() / 2 * unit.first , rect.height() / 2 * unit.second);
        fixture.shape = &Pshape;

    }
    else{

        Cshape.m_radius = rect.width() / 2 * unit.first;
        fixture.shape = &Cshape;

    }


    body = world->CreateBody(&def);
    body->CreateFixture(&fixture);
    body->SetAngularDamping(3);
    body->SetGravityScale(1);

    HP = body->GetMass() * 30 * HPscale;

    size = QSizeF(rect.width() , rect.height());

    exterior = new QGraphicsPixmapItem(pix);
    exterior->setTransformOriginPoint(exterior->boundingRect().width() / 2 , exterior->boundingRect().height() / 2);

    scene->addItem(exterior);
    connect(timer , SIGNAL(timeout()) , this , SLOT(paint()));

    paint();

}

Object::~Object(){}

void Object::collision(Item *other){

    if(!other->getMass())
        HP -= body->GetMass() * qSqrt(qPow(body->GetLinearVelocity().x , 2) + qPow(body->GetLinearVelocity().y , 2));
    else if(0 < other->getMass() && other->getMass() <= 80)
        HP -= other->getMass() * qSqrt(qPow(other->getVelocity().x - body->GetLinearVelocity().x , 2) + qPow(other->getVelocity().y - body->GetLinearVelocity().y , 2));
    else if(80 < other->getMass())
        HP -= other->getMass() * qSqrt(qPow(other->getVelocity().x - body->GetLinearVelocity().x , 2) + qPow(other->getVelocity().y - body->GetLinearVelocity().y , 2));

    if(HP <= 0) Deathflag = true;

}
