#include "GameEngine.h"

void GameEngine::init(const std::string& path) {}

void GameEngine::update() {}

void GameEngine::sUserInput() {}

std::shared_ptr<Scene> GameEngine::currentScene()
{
    return std::shared_ptr<Scene>();
}

GameEngine::GameEngine(const std::string& path) {}

void GameEngine::changeScene(const std::string& sceneName,
                             std::shared_ptr<Scene> scene,
                             bool endCurrentScene)
{
}

void GameEngine::run() {}

void GameEngine::quit() {}

sf::RenderWindow& GameEngine::window()
{
    // TODO: return ステートメントをここに挿入します
}

const Assets& GameEngine::getAssets() const
{
    // TODO: return ステートメントをここに挿入します
}

bool GameEngine::isRunning()
{
    return false;
}
