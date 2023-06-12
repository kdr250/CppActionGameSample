#pragma once

#include <memory>
#include "../ecs/Entity.h"
#include "Vec2.h"

class Physics
{
public:
    static Vec2 getOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);

    static Vec2 getPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
};
