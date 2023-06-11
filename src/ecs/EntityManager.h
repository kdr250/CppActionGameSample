#pragma once

#include <map>
#include <memory>
#include <vector>
#include "Entity.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVector;

class EntityManager
{
private:
    EntityVector m_entities;                          // all entities
    EntityVector m_entitiesToAdd;                     // entities to add next update
    std::map<std::string, EntityVector> m_entityMap;  // map from entity tag to vectors
    size_t m_totalEntities = 0;

    void removeDeadEntities(EntityVector& vec);

public:
    EntityManager();

    void update();
    std::shared_ptr<Entity> addEntity(const std::string& tag);
    EntityVector& getEntities();
    EntityVector& getEntities(const std::string& tag);
};
