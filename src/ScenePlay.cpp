#include "ScenePlay.h"
#include <cmath>
#include <iostream>
#include "GameEngine.h"
#include "Physics.h"

void ScenePlay::init(const std::string& levelPath)
{
    registerAction(sf::Keyboard::P, "PAUSE");
    registerAction(sf::Keyboard::Escape, "QUIT");
    registerAction(sf::Keyboard::T, "TOGGLE_TEXTURE");
    registerAction(sf::Keyboard::C, "TOGGLE_COLLISION");
    registerAction(sf::Keyboard::G, "TOGGLE_GRID");

    // TODO: Register all other gameplay actions
    registerAction(sf::Keyboard::W, "UP");

    m_gridText.setCharacterSize(12);
    m_gridText.setFont(m_game->getAssets().getFont("Roboto-Light.ttf"));

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
    brick->addComponent<CTransform>(Vec2(224, 600));
    brick->getComponent<CTransform>().scale = Vec2(5, 5);
    brick->addComponent<CBoundingBox>(Vec2(80, 80));

    auto brick2 = m_entityManager.addEntity("tile");
    brick2->addComponent<CAnimation>(m_game->getAssets().getAnimation("Brick"), true);
    brick2->addComponent<CTransform>(Vec2(304, 520));
    brick2->getComponent<CTransform>().scale = Vec2(5, 5);
    brick2->addComponent<CBoundingBox>(Vec2(80, 80));

    /*auto block = m_entityManager.addEntity("tile");
    block->addComponent<CAnimation>(m_game->getAssets().getAnimation("Block"), true);
    block->addComponent<CTransform>(Vec2(224, 480));
    block->addComponent<CBoundingBox>(m_game->getAssets().getAnimation("Block").getSize());

    auto question = m_entityManager.addEntity("tile");
    question->addComponent<CAnimation>(m_game->getAssets().getAnimation("Question"), true);
    question->addComponent<CTransform>(Vec2(352, 480));*/
}

ScenePlay::ScenePlay(GameEngine* gameEngie, const std::string& levelPath) :
    Scene(gameEngie), m_levelPath(levelPath)
{
    init(m_levelPath);
}

void ScenePlay::update()
{
    m_entityManager.update();

    // TODO: Implement pause functionality

    sMovement();
    sLifeSpan();
    sCollision();
    sAnimation();
    sRender();
}

void ScenePlay::spawnPlayer()
{
    m_player = m_entityManager.addEntity("player");
    m_player->addComponent<CAnimation>(m_game->getAssets().getAnimation("Idle"), true);
    m_player->addComponent<CTransform>(Vec2(224, 352));
    m_player->getComponent<CTransform>().scale = Vec2(5, 5);
    m_player->addComponent<CBoundingBox>(Vec2(80, 80));
    m_player->addComponent<CGravity>(0.1);
}

void ScenePlay::sAnimation()
{
    if (m_player->getComponent<CState>().state == "air"
        && m_player->getComponent<CAnimation>().animation.getName() != "Air")
    {
        m_player->addComponent<CAnimation>(m_game->getAssets().getAnimation("Air"));
    }
    if (m_player->getComponent<CState>().state == "run"
        && m_player->getComponent<CAnimation>().animation.getName() != "Run")
    {
        m_player->addComponent<CAnimation>(m_game->getAssets().getAnimation("Run"));
    }
    if (m_player->getComponent<CState>().state == "idle"
        && m_player->getComponent<CAnimation>().animation.getName() != "Idle")
    {
        m_player->addComponent<CAnimation>(m_game->getAssets().getAnimation("Idle"));
    }

    // TODO: for each entity with an animation, call entity->getComponent<CAnimation>().animation.update()
    //       if the animation is not repeated, and it has ended, destroy the entity

    m_player->getComponent<CAnimation>().animation.update();
}

void ScenePlay::sMovement()
{
    Vec2 playerVelocity(0, m_player->getComponent<CTransform>().velocity.y);

    if (m_player->getComponent<CInput>().up)
    {
        m_player->getComponent<CState>().state = "air";
        playerVelocity.y                       = -3;
    }

    m_player->getComponent<CTransform>().velocity = playerVelocity;

    for (auto entity : m_entityManager.getEntities())
    {
        if (entity->hasComponent<CGravity>())
        {
            entity->getComponent<CTransform>().velocity.y +=
                entity->getComponent<CGravity>().gravity;
        }
        entity->getComponent<CTransform>().previoutPosition =
            entity->getComponent<CTransform>().position;
        entity->getComponent<CTransform>().position += entity->getComponent<CTransform>().velocity;
    }

    // TODO: Implement the maximum player speed in both X and Y directions
    // NOTE: Setting an entity's scale.x to -1/1 will make it face to the left/right
}

void ScenePlay::sLifeSpan()
{
    // TODO: Check lifespan of entities that have them, and destroy them if they go over
}

void ScenePlay::sEnemySpawner() {}

void ScenePlay::sCollision()
{
    for (auto entity : m_entityManager.getEntities("tile"))
    {
        Vec2 overlap = Physics::getOverlap(m_player, entity);
        if (overlap.x > 0 && overlap.y > 0)
        {
            Vec2 previousOverlap = Physics::getPreviousOverlap(m_player, entity);
            if (previousOverlap.x > 0
                && m_player->getComponent<CTransform>().previoutPosition.y
                       < entity->getComponent<CTransform>().previoutPosition.y)
            {
                m_player->getComponent<CTransform>().position.y -= overlap.y;
            }
            else if (previousOverlap.x > 0
                     && m_player->getComponent<CTransform>().previoutPosition.y
                            > entity->getComponent<CTransform>().previoutPosition.y)
            {
                m_player->getComponent<CTransform>().position.y += overlap.y;
            }
            if (previousOverlap.y > 0
                && m_player->getComponent<CTransform>().previoutPosition.x
                       < entity->getComponent<CTransform>().previoutPosition.x)
            {
                m_player->getComponent<CTransform>().position.x -= overlap.x;
            }
            else if (previousOverlap.y > 0
                     && m_player->getComponent<CTransform>().previoutPosition.x
                            < entity->getComponent<CTransform>().previoutPosition.x)
            {
                m_player->getComponent<CTransform>().position.x += overlap.x;
            }
        }
    }
}

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
    if (m_drawCollision)
    {
        for (auto entity : m_entityManager.getEntities())
        {
            if (entity->hasComponent<CBoundingBox>())
            {
                auto& box       = entity->getComponent<CBoundingBox>();
                auto& transform = entity->getComponent<CTransform>();
                sf::RectangleShape rectangle;
                rectangle.setSize(sf::Vector2f(box.size.x - 1, box.size.y - 1));
                rectangle.setOrigin(sf::Vector2f(box.halfSize.x, box.halfSize.y));
                rectangle.setPosition(transform.position.x, transform.position.y);
                rectangle.setFillColor(sf::Color(0, 0, 0, 0));
                rectangle.setOutlineColor(sf::Color(255, 255, 255, 255));
                rectangle.setOutlineThickness(1);
                m_game->window().draw(rectangle);
            }
        }
    }

    // draw the grid so that developer can easily debug
    if (m_drawGrid)
    {
        float leftX     = m_game->window().getView().getCenter().x - width() / 2;
        float rightX    = leftX + width() + m_gridSize.x;
        float nextGridX = leftX - ((int)leftX & (int)m_gridSize.x);

        for (float x = nextGridX; x < rightX; x += m_gridSize.x)
        {
            drawLine(Vec2(x, 0), Vec2(x, height()));
        }

        for (float y = 0; y < height(); y += m_gridSize.x)
        {
            drawLine(Vec2(leftX, height() - y), Vec2(rightX, height() - y));

            for (float x = nextGridX; x < rightX; x += m_gridSize.x)
            {
                std::string xCell = std::to_string((int)x / (int)m_gridSize.x);
                std::string yCell = std::to_string((int)y / (int)m_gridSize.y);
                m_gridText.setString("(" + xCell + ", " + yCell + ")");
                m_gridText.setPosition(x + 3, height() - y - m_gridSize.y + 2);
                m_game->window().draw(m_gridText);
            }
        }
    }
}

void ScenePlay::sDoAction(const Action& action)
{
    if (action.type() == "START")
    {
        if (action.name() == "TOGGLE_TEXTURE")
        {
            m_drawTextures = !m_drawTextures;
        }
        else if (action.name() == "TOGGLE_COLLISION")
        {
            m_drawCollision = !m_drawCollision;
        }
        else if (action.name() == "TOGGLE_GRID")
        {
            m_drawGrid = !m_drawGrid;
        }
        else if (action.name() == "PAUSE")
        {
            setPaused(!m_paused);
        }
        else if (action.name() == "QUIT")
        {
            onEnd();
        }
        else if (action.name() == "UP")
        {
            m_player->getComponent<CInput>().up = true;
        }
    }
    else if (action.type() == "END")
    {
        if (action.name() == "UP")
        {
            m_player->getComponent<CInput>().up = false;
        }
    }
}

void ScenePlay::sDebug() {}

void ScenePlay::onEnd()
{
    // TODO: When the scene ends, change back to the MENU scene
    //       use m_game->changeScene(XXX)
}

Vec2 ScenePlay::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
    // TODO: This function takes in a grid (x,y) position and an Entity
    //       Return a Vec2 indicating where the CENTER position of the Entity should be
    //       You must use the Entity's Animation size to position it correctly
    //       The size of the grid width and height is stored in m_gridSize.x and m_gridSize.y
    //       The bottom-left corner of the Animation should align with the bottom left of the grid cell

    return Vec2();
}
