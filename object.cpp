#include "object.h"

#include <QDebug>
#include <QtMath>

Object::Object(b2World *dim , QPointF point , int type , QGraphicsScene *scene , QTimer *timer , bool Pol , float HPscale):
Item(dim) , hpScale(HPscale)
{

    QRectF rect;

    switch(type){

        case P1X1:

            rect.setRect(point.x() , point.y() , 20 , 20);

            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_1_1.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_2_1.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_3_1.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_4_1.png"));
            break;

        case P2X1:

            rect.setRect(point.x() , point.y() , 40 , 20);

            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_1_2.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_2_2.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_3_2.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_4_2.png"));
            break;

        case P2X2:

            rect.setRect(point.x() , point.y() , 40 ,40);

            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_1_3.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_2_3.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_3_3.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_4_3.png"));
            break;

        case P4X1:

            rect.setRect(point.x() , point.y() , 80 , 20);

            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_1_4.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_2_4.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_3_4.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_4_4.png"));
            break;

        case P4X2:

            rect.setRect(point.x() , point.y() , 80 , 40);

            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_1_5.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_2_5.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_3_5.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_4_5.png"));
            break;

        case P4X4:

            rect.setRect(point.x() , point.y() , 80 , 80);

            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_4X4_1.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_4X4_2.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_4X4_3.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_4X4_4.png"));
            break;

        case P8X1:

            rect.setRect(point.x() , point.y() , 160 , 20);

            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_1_6.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_2_6.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_3_6.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_4_6.png"));
            break;

        case P10X1:

            rect.setRect(point.x() , point.y() , 200 , 20);

            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_10X1_1.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_10X1_2.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_10X1_3.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_10X1_4.png"));
            break;

        case CB:

            rect.setRect(point.x() , point.y() , 75 , 75);

            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_1_7.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_2_7.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_3_7.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_4_7.png"));
            break;

        case CS:

            rect.setRect(point.x() , point.y() , 40 , 40);

            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_1_8.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_2_8.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_3_8.png"));
            image.push_back(QPixmap(":/Resource/BLOCK_WOOD_4_8.png"));
            break;


    }

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

    HP = body->GetMass() * 20 * HPscale;

    size = QSizeF(rect.width() , rect.height());

    exterior = new QGraphicsPixmapItem(image[0]);
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

    if(body->GetMass() * 10 * hpScale < HP && HP <= body->GetMass() * 15 * hpScale) exterior->setPixmap(image[1]);
    else if(body->GetMass() * 5 * hpScale < HP && HP <= body->GetMass() * 10 * hpScale) exterior->setPixmap(image[2]);
    else if(body->GetMass() * 0 * hpScale < HP && HP <= body->GetMass() * 5 * hpScale) exterior->setPixmap(image[3]);

    if(HP <= 0) Deathflag = true;

}
