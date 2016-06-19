#include "bird.h"

#include <QDebug>

Bird::Bird(b2World *dim , QPointF point , float r , QPixmap pix , QGraphicsScene *scene , QTimer *timer):
Item(dim) , CD(false)
{

    b2BodyDef def;
    def.position.Set((point.x() + r) * unit.first , (windowH - point.y() - r) * unit.second);
    def.type = b2_dynamicBody;
    def.userData = this;

    b2CircleShape shape;
    shape.m_radius = r * unit.first;

    b2FixtureDef fixture;
    fixture.density = B_DENSITY;
    fixture.friction = B_FRACTION;
    fixture.restitution = B_RESTITUTION;
    fixture.shape = &shape;

    body = world->CreateBody(&def);
    body->CreateFixture(&fixture);
    body->SetAngularDamping(3);
    body->SetGravityScale(0);

    size = QSizeF(r * 2 , r * 2);

    exterior = new QGraphicsPixmapItem(pix);
    exterior->setZValue(2);
    exterior->setTransformOriginPoint(exterior->boundingRect().width() / 2 , exterior->boundingRect().height() / 2);

    scene->addItem(exterior);
    connect(timer , SIGNAL(timeout()) , this , SLOT(paint()));

    paint();

}

Bird::~Bird(){}

void Bird::setGscale(float scale){body->SetGravityScale(scale);}

void Bird::setCD(bool b){CD = b;}

bool Bird::getCD(){return CD;}

void Bird::feature(){}
