#pragma once

#include "Scene.h"

class ScenePlay : public Scene
{
    struct PlayerConfg
    {
        float X, Y, CX, CY, SPEED, MAXSPEED, JUMP, GRAVITY;
        std::string WEAPONS;
    };

protected:
    std::shared_ptr<Entity> m_player;
    std::string m_levelPath;
    PlayerConfg m_playerConfig;
    bool m_drawTextures   = true;
    bool m_drawCollision  = false;
    bool m_drawGrid       = false;
    const Vec2 m_gridSize = {64, 64};
    sf::Text m_gridText;

    void init(const std::string& levelPath);

    void loadLevel(const std::string& filename);

public:
    ScenePlay(GameEngine* gameEngie, const std::string& levelPath);

    void update();

    void spawnPlayer();
    void spawnBullet();

    void sAnimation();
    void sMovement();
    void sLifeSpan();
    void sEnemySpawner();
    void sCollision();
    void sRender();
    void sDebug();

    virtual void onEnd() override;
    virtual void sDoAction(const Action& action) override;

    Vec2 gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);
};
