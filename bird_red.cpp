#include "bird_red.h"

//Bird(b2World *dim , float x , float y , float r , QPixmap pix , QGraphicsScene *scene)

Bird_red::Bird_red(b2World *dim , float x , float y , QGraphicsScene *scene):
Bird(dim , x , y , 20 , QPixmap(":/Resource/BIRD_RED.png") , scene)
{}
