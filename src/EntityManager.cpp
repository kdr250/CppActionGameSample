#include "EntityManager.h"

void EntityManager::removeDeadEntities(EntityVector& vec)
{
    auto result = std::remove_if(vec.begin(),
                                 vec.end(),
                                 [](std::shared_ptr<Entity>& entity)
                                 {
                                     return !entity->isActive();
                                 });
    vec.erase(result, vec.end());
}

EntityManager::EntityManager() {}

void EntityManager::update()
{
    for (auto entity : m_entitiesToAdd)
    {
        m_entities.push_back(entity);
        m_entityMap[entity->tag()].push_back(entity);
    }

    m_entitiesToAdd.clear();

    removeDeadEntities(m_entities);

    for (auto& [tag, vec] : m_entityMap)
    {
        removeDeadEntities(vec);
    }
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
    auto entity = std::make_shared<Entity>(m_totalEntities, tag);
    m_entitiesToAdd.push_back(entity);
    m_totalEntities++;
    return entity;
}

EntityVector& EntityManager::getEntities()
{
    return m_entities;
}

EntityVector& EntityManager::getEntities(const std::string& tag)
{
    return m_entityMap[tag];
}
