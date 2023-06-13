#include "Physics.h"
#include <cmath>

/**
   return the overlap rectangle size of the bouding box of entity a and b
*/
Vec2 Physics::getOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
    auto& transformA   = a->getComponent<CTransform>();
    auto& boundingBoxA = a->getComponent<CBoundingBox>();
    auto& transformB   = b->getComponent<CTransform>();
    auto& boundingBoxB = b->getComponent<CBoundingBox>();

    float distanceX = std::abs(transformA.position.x - transformB.position.x);
    float distanceY = std::abs(transformA.position.y - transformB.position.y);

    float ox = boundingBoxA.halfSize.x + boundingBoxB.halfSize.x - distanceX;
    float oy = boundingBoxA.halfSize.y + boundingBoxB.halfSize.y - distanceY;

    return Vec2(ox, oy);
}

/**
   return the previous overlap rectangle size of the bouding boxes of entity a and b
   previous overlap uses the entity's previous position
*/
Vec2 Physics::getPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
    auto& transformA   = a->getComponent<CTransform>();
    auto& boundingBoxA = a->getComponent<CBoundingBox>();
    auto& transformB   = b->getComponent<CTransform>();
    auto& boundingBoxB = b->getComponent<CBoundingBox>();

    float distanceX = std::abs(transformA.previousPosition.x - transformB.previousPosition.x);
    float distanceY = std::abs(transformA.previousPosition.y - transformB.previousPosition.y);

    float ox = boundingBoxA.halfSize.x + boundingBoxB.halfSize.x - distanceX;
    float oy = boundingBoxA.halfSize.y + boundingBoxB.halfSize.y - distanceY;

    return Vec2(ox, oy);
}
