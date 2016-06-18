#include "lv0.h"

LV0::LV0(b2World *dim , float x , float y , QGraphicsScene *scene , QTimer *timer):
Bird(dim , x , y , 15 , QPixmap(":/Resource/BIRD_RED.png") , scene , timer)
{}
