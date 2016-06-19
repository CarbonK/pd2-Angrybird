#include "accelerator.h"

Accelerator::Accelerator(b2World *dim , QPointF point , QGraphicsScene *scene , QTimer *timer):
Bird(dim , point , 15 , QPixmap(":/Resource/BIRD_YELLOW.png") , scene , timer)
{}

void Accelerator::feature(){

    setVelocity(body->GetLinearVelocity().x * 5 , body->GetLinearVelocity().y * 5);
    setCD(true);

}
