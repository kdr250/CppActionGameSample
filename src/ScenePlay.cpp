#include "ScenePlay.h"
#include "GameEngine.h"

void ScenePlay::init(const std::string& levelPath)
{
    registerAction(sf::Keyboard::P, "PAUSE");
    registerAction(sf::Keyboard::Escape, "QUIT");
    registerAction(sf::Keyboard::T, "TOGGLE_TEXTURE");
    registerAction(sf::Keyboard::C, "TOGGLE_COLLISION");
    registerAction(sf::Keyboard::G, "TOGGLE_GRID");

    // TODO: Register all other gameplay actions

    m_gridText.setCharacterSize(12);
    m_gridText.setFont(m_game->getAssets().getFont("Roboto-Light.ttf");

    loadLevel(levelPath);
}

void ScenePlay::loadLevel(const std::string& filename) {}

ScenePlay::ScenePlay(GameEngine* gameEngie, const std::string& levelPath) :
    Scene(gameEngie), m_levelPath(levelPath)
{
    init(m_levelPath);
}

void ScenePlay::update() {}

void ScenePlay::sAnimation() {}

void ScenePlay::sMovement() {}

void ScenePlay::sEnemySpawner() {}

void ScenePlay::SCollision() {}

void ScenePlay::sRender() {}

void ScenePlay::sDoAction(Action& action) {}

void ScenePlay::sDebug() {}

void ScenePlay::onEnd() {}

void ScenePlay::sDoAction(const Action& action) {}

Vec2 ScenePlay::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
    return Vec2();
}
