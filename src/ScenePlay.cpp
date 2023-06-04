#include "ScenePlay.h"
#include <cmath>
#include "GameEngine.h"

void ScenePlay::init(const std::string& levelPath)
{
    registerAction(sf::Keyboard::P, "PAUSE");
    registerAction(sf::Keyboard::Escape, "QUIT");
    registerAction(sf::Keyboard::T, "TOGGLE_TEXTURE");
    registerAction(sf::Keyboard::C, "TOGGLE_COLLISION");
    registerAction(sf::Keyboard::G, "TOGGLE_GRID");

    // TODO: Register all other gameplay actions
    registerAction(sf::Keyboard::W, "JUMP");

    m_gridText.setCharacterSize(12);
    m_gridText.setFont(m_game->getAssets().getFont("Roboto-Light.ttf");

    loadLevel(levelPath);
}

void ScenePlay::loadLevel(const std::string& filename)
{
    // reset the entity manager every time we load a level
    m_entityManager = EntityManager();

    // TODO: read in the level file and add the appropriate entities
    //       use the PlayerConfig struct m_playerConfig to store player properties

    // NOTE: all of the code below is sample code, it should be removed
    spawnPlayer();

    auto brick = m_entityManager.addEntity("tile");
    brick->addComponent<CAnimation>(m_game->getAssets().getAnimation("Brick"), true);
    brick->addComponent<CTransform>(Vec2(96,　480));
    if (brick->getComponent<CAnimation>().animation.getName() == "Brick")
    {
        std::count << "This could be a good way of identifying if a tile is a brick" << std::endl;
    }

    auto block = m_entityManager.addEntity("tile");
    block->addComponent<CAnimation>(m_game->getAssets().getAnimation("Block"), true);
    block->addComponent<CTransform>(Vec2(224, 480));
    block->addComponent<CBoundingBox>(m_game->getAssets().getAnimation("Block").getSize());

    auto question = m_entityManager.addEntity("tile");
    question->addComponent<CAnimation>(m_game->getAssets().getAnimation("Question"), true);
    question->addComponent<CTransform>(Vec2(352, 480));
}

ScenePlay::ScenePlay(GameEngine* gameEngie, const std::string& levelPath) :
    Scene(gameEngie), m_levelPath(levelPath)
{
    init(m_levelPath);
}

void ScenePlay::update()
{
    // TODO: Implement pause functionality

    sMovement();
    sLifeSpan();
    sCollision();
    sAnimation();
    sRender();
}

void ScenePlay::spawnPlayer() {}

void ScenePlay::sAnimation() {}

void ScenePlay::sMovement()
{
    Vec2 playerVelocity(0, 0);

    if (m_player->getComponent<CInput>().up)
    {
        playerVelocity.y = -3;
    }

    m_player->getComponent<CTransform>().velocity = playerVelocity;

    for (auto entity : m_entityManager.getEntities())
    {
        entity->getComponent<CTransform>().position += entity->getComponent<CTransform>().velocity;
    }

    // TODO: Implement gravity's effect on the player
    // TODO: Implement the maximum player speed in both X and Y directions
    // NOTE: Setting an entity's scale.x to -1/1 will make it face to the left/right
}

void ScenePlay::sLifeSpan() {}

void ScenePlay::sEnemySpawner() {}

void ScenePlay::sCollision() {}

void ScenePlay::sRender()
{
    if (!m_paused)
    {
        m_game->window().clear(sf::Color(100, 100, 255));
    }
    else
    {
        m_game->window().clear(sf::Color(50, 50, 150));
    }

    // set the viewport of the window to be centered on the player if it's far enough right
    auto& playerPosition = m_player->getComponent<CTransform>().position;
    float windowCenterX  = std::max(m_game->window().getSize().x / 2.0f, playerPosition.x);
    sf::View view        = m_game->window().getView();
    view.setCenter(windowCenterX, m_game->window().getSize().y - view.getCenter().y);
    m_game->window().setView(view);

    // draw all Entity textures / animations
    if (m_drawTextures)
    {
        for (auto entity : m_entityManager.getEntities())
        {
            auto& transform = entity->getComponent<CTransform>();

            if (entity->hasComponent<CAnimation>())
            {
                auto& animation = entity->getComponent<CAnimation>().animation;
                animation.getSprite().setRotation(transform.angle);
                animation.getSprite().setPosition(transform.position.x, transform.position.y);
                animation.getSprite().setScale(transform.scale.x, transform.scale.y);
                m_game->window().draw(animation.getSprite());
            }
        }
    }

    // draw all Entity collision bouding boxes with a rectangle shape
}

void ScenePlay::sDoAction(Action& action)
{
    if (action.type() == "START")
    {
        switch (action.name())
        {
            case "TOGGLE_TEXTURE":
                m_drawTextures = !m_drawTextures;
                break;
            case "TOGGLE_COLLISION":
                m_drawCollision = !m_drawCollision;
                break;
            case "TOGGLE_GRID":
                m_drawGrid = !m_drawGrid;
                break;
            case "PAUSE":
                setPaused(!m_paused);
                break;
            case "QUIT":
                onEnd();
                break;
            // TODO: Implement other actions
            case "JUMP":
                // TODO: player's input component
                break;
            default:
                break;
        }
    }
    else if (action.type() == "END")
    {
    }
}

void ScenePlay::sDebug() {}

void ScenePlay::onEnd() {}

void ScenePlay::sDoAction(const Action& action) {}

Vec2 ScenePlay::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
    return Vec2();
}
