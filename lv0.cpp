#include "lv0.h"

LV0::LV0(b2World *dim , QPointF point , QGraphicsScene *scene , QTimer *timer):
Bird(dim , point , 15 , QPixmap(":/Resource/BIRD_RED.png") , scene , timer)
{}
