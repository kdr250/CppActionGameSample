#include "Scene.h"
#include "../GameEngine.h"

void Scene::setPaused(bool paused) {}

Scene::Scene() {}

Scene::Scene(GameEngine* gameEngine) : m_game(gameEngine) {}

void Scene::simulate(const size_t frames) {}

void Scene::registerAction(int inputKey, const std::string& actionName)
{
    m_actionMap[inputKey] = actionName;
}

size_t Scene::width() const
{
    return size_t();
}

size_t Scene::height() const
{
    return size_t();
}

size_t Scene::currentFrame() const
{
    return size_t();
}

bool Scene::hasEnded() const
{
    return false;
}

const ActionMap& Scene::getActionMap() const
{
    return m_actionMap;
}

void Scene::drawLine(const Vec2& p1, const Vec2& p2) {}
