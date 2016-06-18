#include "accelerator.h"

Accelerator::Accelerator(b2World *dim , float x , float y , QGraphicsScene *scene , QTimer *timer):
    Bird(dim , x , y , 15 , QPixmap(":/Resource/BIRD_YELLOW.png") , scene , timer)
{}

void Accelerator::feature(){setVelocity(body->GetLinearVelocity().x * 2 , body->GetLinearVelocity().y * 2);}
