#ifndef COLLISIONCONTECTER_H
#define COLLISIONCONTECTER_H

#include "item.h"

#include <Box2D/Box2D.h>

class CollisionContecter:
public b2ContactListener
{

    public:

        CollisionContecter();
        void EndContact(b2Contact *contact);

};

#endif // COLLISIONCONTECTER_H
