#include "megumi.h"

#include "QMovie"

Megumi::Megumi(b2World *dim, QPointF point, QGraphicsScene *scene, QTimer *timer):
Bird(dim , point , 50 , QPixmap(":/Resource/megumi.png") , scene , timer)
{}

void Megumi::feature(){emit explosion();}
