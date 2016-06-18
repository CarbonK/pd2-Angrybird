#include "piggie.h"

#include <QDebug>
#include <QtMath>

Piggie::Piggie(b2World *dim , float x , float y , float r , int type , QGraphicsScene *scene , QTimer *timer):
Item(dim)
{

    switch(type){

        case small:

            image.push_back(QPixmap(":/Resource/PIGLETTE_SMALL_01.png"));
            image.push_back(QPixmap(":/Resource/PIGLETTE_SMALL_02.png"));
            image.push_back(QPixmap(":/Resource/PIGLETTE_SMALL_03.png"));
            break;

        case medium:

            image.push_back(QPixmap(":/Resource/PIGLETTE_MEDIUM_01.png"));
            image.push_back(QPixmap(":/Resource/PIGLETTE_MEDIUM_02.png"));
            image.push_back(QPixmap(":/Resource/PIGLETTE_MEDIUM_03.png"));
            break;

        case helmet:

            image.push_back(QPixmap(":/Resource/PIGLETTE_HELMET_01.png"));
            image.push_back(QPixmap(":/Resource/PIGLETTE_HELMET_02.png"));
            image.push_back(QPixmap(":/Resource/PIGLETTE_HELMET_03.png"));
            break;

        case king:

            image.push_back(QPixmap(":/Resource/PIGLETTE_KING_01.png"));
            image.push_back(QPixmap(":/Resource/PIGLETTE_KING_02.png"));
            image.push_back(QPixmap(":/Resource/PIGLETTE_KING_03.png"));
            break;

    }

    b2BodyDef def;
    def.position.Set((x + r) * unit.first , (windowH - y - r) * unit.second);
    def.type = b2_dynamicBody;
    def.userData = this;

    b2CircleShape shape;
    shape.m_radius = r * unit.first;

    b2FixtureDef fixture;
    fixture.density = P_DENSITY;
    fixture.friction = P_FRACTION;
    fixture.restitution = P_RESTITUTION;
    fixture.shape = &shape;

    body = world->CreateBody(&def);
    body->CreateFixture(&fixture);
    body->SetAngularDamping(3);

    HP = body->GetMass() * 3;

    size = QSizeF(r * 2 , r * 2);

    exterior = new QGraphicsPixmapItem(image[0]);
    exterior->setTransformOriginPoint(exterior->boundingRect().width() / 2 , exterior->boundingRect().height() / 2);

    scene->addItem(exterior);
    connect(timer , SIGNAL(timeout()) , this , SLOT(paint()));

    paint();

}

void Piggie::collision(Item *other){

    if(!other->getMass())
        HP -= body->GetMass() * qSqrt(qPow(body->GetLinearVelocity().x , 2) + qPow(body->GetLinearVelocity().y , 2));
    else if(0 < other->getMass() && other->getMass() <= 80)
        HP -= other->getMass() * qSqrt(qPow(other->getVelocity().x - body->GetLinearVelocity().x , 2) + qPow(other->getVelocity().y - body->GetLinearVelocity().y , 2));
    else if(80 < other->getMass())
        HP -= other->getMass() * qSqrt(qPow(other->getVelocity().x - body->GetLinearVelocity().x , 2) + qPow(other->getVelocity().y - body->GetLinearVelocity().y , 2));

    if(body->GetMass() < HP && HP <= body->GetMass() * 2) exterior->setPixmap(image[1]);
    else if(0 < HP && HP <= body->GetMass()) exterior->setPixmap(image[2]);

    if(HP <= 0) Deathflag = true;

}
