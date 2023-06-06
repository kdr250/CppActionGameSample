#include "Physics.h"

/**
   return the overlap rectangle size of the bouding box of entity a and b
*/
Vec2 Physics::getOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
    auto& position = a->getComponent<CTransform>();

    return Vec2();
}

/**
   return the previous overlap rectangle size of the bouding boxes of entity a and b
   previous overlap uses the entity's previous position
*/
Vec2 Physics::getPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
    return Vec2();
}
