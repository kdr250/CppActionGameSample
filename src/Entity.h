#pragma once

#include <string>
#include <tuple>
#include "Components.h"

class EntityManager;

typedef std::tuple<CTransform, CLifespan, CInput, CBoundingBox, CAnimation, CGravity, CState>
    ComponentTuple;

class Entity
{
    friend class EntityManager;

private:
    bool m_active     = true;
    std::string m_tag = "default";
    size_t m_id       = 0;
    ComponentTuple m_components;

    Entity(const size_t& id, const std::string& tag);

public:
    void destroy();
    size_t id() const;
    bool isActive() const;
    const std::string& tag() const;

    template<typename T>
    bool hasComponent() const
    {
        return getComponent<T>.has();
    }

    template<typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        auto& component = getComponent<T>();
        component       = T(std::forward<TArgs>(mArgs)...);
        component.has   = true;
        return component;
    }

    template<typename T>
    T& getComponent()
    {
        return std::get<T>(m_components);
    }
};
