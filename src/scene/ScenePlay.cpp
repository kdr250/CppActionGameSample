#include "ScenePlay.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "../GameEngine.h"
#include "../physics/Physics.h"

void ScenePlay::init(const std::string& levelPath)
{
    registerAction(sf::Keyboard::P, "PAUSE");
    registerAction(sf::Keyboard::Escape, "QUIT");
    registerAction(sf::Keyboard::T, "TOGGLE_TEXTURE");
    registerAction(sf::Keyboard::C, "TOGGLE_COLLISION");
    registerAction(sf::Keyboard::G, "TOGGLE_GRID");

    registerAction(sf::Keyboard::W, "UP");
    registerAction(sf::Keyboard::A, "LEFT");
    registerAction(sf::Keyboard::D, "RIGHT");
    registerAction(sf::Keyboard::Space, "SHOOT");

    m_gridText.setCharacterSize(12);
    m_gridText.setFont(m_game->getAssets().getFont("Roboto-Light.ttf"));

    loadLevel(levelPath);
}

void ScenePlay::loadLevel(const std::string& filename)
{
    // reset the entity manager every time we load a level
    m_entityManager = EntityManager();

    std::ifstream file;
    file.open(m_levelPath);
    if (!file.is_open())
    {
        std::cout << "Failed to load level file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::vector<std::string> allLine;

    while (std::getline(file, line))
    {
        allLine.push_back(line);
    }

    file.close();

    for (auto& line : allLine)
    {
        std::stringstream levelstream(line);
        std::string type;
        levelstream >> type;
        if (type == "Tile")
        {
            std::string name;
            float gridX;
            float gridY;
            levelstream >> name >> gridX >> gridY;
            auto tile = m_entityManager.addEntity("tile");
            tile->addComponent<CAnimation>(m_game->getAssets().getAnimation(name), true);
            tile->addComponent<CTransform>(gridToMidPixel(gridX, gridY, tile),
                                           tile->getComponent<CAnimation>().animation.getScale());
            tile->addComponent<CBoundingBox>(tile->getComponent<CAnimation>().animation.getSize());
        }
        else if (type == "Player")
        {
            levelstream >> m_playerConfig.X >> m_playerConfig.Y >> m_playerConfig.CX
                >> m_playerConfig.CY >> m_playerConfig.SPEED >> m_playerConfig.MAXSPEED
                >> m_playerConfig.JUMP >> m_playerConfig.GRAVITY >> m_playerConfig.WEAPONS;
        }
    }

    spawnPlayer();
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
    m_player->addComponent<CTransform>(Vec2(224, 352),
                                       m_player->getComponent<CAnimation>().animation.getScale());
    m_player->addComponent<CBoundingBox>(m_player->getComponent<CAnimation>().animation.getSize());
    m_player->addComponent<CGravity>(m_playerConfig.GRAVITY);
}

void ScenePlay::spawnBullet()
{
    if (m_player->getComponent<CInput>().shoot)
    {
        // TODO: Not Yet Implemented
    }
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

    for (auto bullet : m_entityManager.getEntities("bullet"))
    {
        bullet->getComponent<CTransform>().angle += 10.0;
    }
}

void ScenePlay::sMovement()
{
    Vec2 playerVelocity(0, m_player->getComponent<CTransform>().velocity.y);

    if (m_player->getComponent<CInput>().up
        && m_player->getComponent<CInput>().upCount <= CInput::MAX_UP_COUNT)
    {
        m_player->getComponent<CInput>().upCount++;
        m_player->getComponent<CState>().state = "air";
        playerVelocity.y                       = -m_playerConfig.JUMP;
    }
    if (m_player->getComponent<CInput>().left)
    {
        if (m_player->getComponent<CState>().state != "air")
        {
            m_player->getComponent<CState>().state = "run";
        }
        playerVelocity.x = -m_playerConfig.SPEED;
    }
    else if (m_player->getComponent<CInput>().right)
    {
        if (m_player->getComponent<CState>().state != "air")
        {
            m_player->getComponent<CState>().state = "run";
        }
        playerVelocity.x = m_playerConfig.SPEED;
        playerVelocity.x = m_playerConfig.SPEED;
    }
    if (m_player->getComponent<CInput>().shoot && m_player->getComponent<CInput>().canShoot)
    {
        auto& playerTransform = m_player->getComponent<CTransform>();
        float bulletVelocityX = playerTransform.scale.x >= 0 ? 15.0f : -15.0f;

        auto bullet = m_entityManager.addEntity("bullet");
        bullet->addComponent<CAnimation>(m_game->getAssets().getAnimation("Bullet"), true);
        bullet->addComponent<CTransform>(playerTransform.position,
                                         Vec2(bulletVelocityX, 0),
                                         bullet->getComponent<CAnimation>().animation.getScale());

        m_player->getComponent<CInput>().canShoot = false;
    }

    m_player->getComponent<CTransform>().velocity = playerVelocity;

    for (auto entity : m_entityManager.getEntities())
    {
        if (entity->hasComponent<CGravity>())
        {
            entity->getComponent<CTransform>().velocity.y +=
                entity->getComponent<CGravity>().gravity;
        }
        entity->getComponent<CTransform>().previousPosition =
            entity->getComponent<CTransform>().position;
        entity->getComponent<CTransform>().position += entity->getComponent<CTransform>().velocity;

        if ((entity->getComponent<CTransform>().velocity.x < 0
             && entity->getComponent<CTransform>().scale.x > 0)
            || (entity->getComponent<CTransform>().velocity.x > 0
                && entity->getComponent<CTransform>().scale.x < 0))
        {
            entity->getComponent<CTransform>().scale.x *= -1;
        }
    }
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
                && m_player->getComponent<CTransform>().previousPosition.y
                       < entity->getComponent<CTransform>().previousPosition.y)
            {
                auto& transform = m_player->getComponent<CTransform>();
                transform.position.y -= overlap.y;
                transform.velocity.y                     = 0;
                m_player->getComponent<CInput>().upCount = 0;
                m_player->getComponent<CState>().state   = "run";
            }
            else if (previousOverlap.x > 0
                     && m_player->getComponent<CTransform>().previousPosition.y
                            > entity->getComponent<CTransform>().previousPosition.y)
            {
                m_player->getComponent<CTransform>().position.y += overlap.y;
            }
            if (previousOverlap.y > 0
                && m_player->getComponent<CTransform>().previousPosition.x
                       < entity->getComponent<CTransform>().previousPosition.x)
            {
                m_player->getComponent<CTransform>().position.x -= overlap.x;
            }
            else if (previousOverlap.y > 0
                     && m_player->getComponent<CTransform>().previousPosition.x
                            > entity->getComponent<CTransform>().previousPosition.x)
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
            if (m_player->getComponent<CInput>().upCount == 0)
            {
                m_player->getComponent<CInput>().up = true;
            }
            else
            {
                m_player->getComponent<CInput>().up = false;
            }
        }
        else if (action.name() == "LEFT")
        {
            m_player->getComponent<CInput>().left = true;
        }
        else if (action.name() == "RIGHT")
        {
            m_player->getComponent<CInput>().right = true;
        }
        else if (action.name() == "SHOOT")
        {
            m_player->getComponent<CInput>().shoot = true;
        }
    }
    else if (action.type() == "END")
    {
        if (action.name() == "UP")
        {
            m_player->getComponent<CInput>().up = false;
        }
        else if (action.name() == "LEFT")
        {
            m_player->getComponent<CInput>().left = false;
        }
        else if (action.name() == "RIGHT")
        {
            m_player->getComponent<CInput>().right = false;
        }
        else if (action.name() == "SHOOT")
        {
            m_player->getComponent<CInput>().shoot    = false;
            m_player->getComponent<CInput>().canShoot = true;
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
    float maxWidth  = (float)m_game->window().getSize().x;
    float maxHeight = (float)m_game->window().getSize().y;

    float minusX = gridX * m_gridSize.x;
    float minusY = gridY * m_gridSize.y;

    float animX = entity->getComponent<CAnimation>().animation.getSize().x / 2.0f;
    float animY = entity->getComponent<CAnimation>().animation.getSize().y / 2.0f;

    return Vec2(minusX + animX, maxHeight - minusY - animY);
}
