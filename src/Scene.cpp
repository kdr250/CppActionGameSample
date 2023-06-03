#include "Scene.h"
#include "GameEngine.h"

void Scene::setPaused(bool paused) {}

Scene::Scene() {}

Scene::Scene(GameEngine* gameEngine) {}

void Scene::doAction(const Action& action) {}

void Scene::simulate(const size_t frames) {}

void Scene::registerAction(int inputKey, const std::string& actionName) {}

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
    // TODO: return ステートメントをここに挿入します
}

void Scene::drawLine(const Vec2& p1, const Vec2& p2) {}
