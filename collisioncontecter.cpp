#include "collisioncontecter.h"

CollisionContecter::CollisionContecter(){}

void CollisionContecter::EndContact(b2Contact *contact)
{

    static_cast<Item *>(contact->GetFixtureA()->GetBody()->GetUserData())->collision(static_cast<Item *>(contact->GetFixtureB()->GetBody()->GetUserData()));
    static_cast<Item *>(contact->GetFixtureB()->GetBody()->GetUserData())->collision(static_cast<Item *>(contact->GetFixtureA()->GetBody()->GetUserData()));

}
