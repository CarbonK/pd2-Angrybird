#include "bomber.h"

#include "QtMath"

Bomber::Bomber(b2World *dim , QPointF point , QGraphicsScene *scene , QTimer *timer):
Bird(dim , point , 17.5 , QPixmap(":/Resource/BIRD_GREY.png") , scene , timer)
{}

void Bomber::feature(){

    if(getCD()) return;

    b2Vec2 B = getBody()->GetPosition();
    b2Body *list = world->GetBodyList();

    for(int i = 0 ; i < world->GetBodyCount() ; ++i , list = list->GetNext()){

        b2Vec2 O = list->GetPosition();
        float dis = qSqrt(qPow(B.x - O.x , 2) + qPow(B.y - O.y , 2));

        if(dis < 10) static_cast<Item *>(list->GetUserData())->setDeathflag(true);
        else if(10 <= dis && dis < 30) list->ApplyForceToCenter(b2Vec2((O.x - B.x) * 30000 , (O.y - B.y) * 30000) , true);

    }

    this->setDeathflag(true);

    setCD(true);

}
