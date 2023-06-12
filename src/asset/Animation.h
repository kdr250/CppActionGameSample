#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "../physics/Vec2.h"

class Animation
{
private:
    sf::Sprite m_sprite;
    int m_frameCount;
    int m_currentFrame;
    int m_speed;
    Vec2 m_size;
    std::string m_name;
    float m_scale;

public:
    Animation();
    Animation(const std::string& name, const sf::Texture& t);
    Animation(const std::string& name,
              const sf::Texture& t,
              int frameCount,
              int speed,
              float scale);

    void update();

    std::string& getName();
    Vec2 getSize();
    sf::Sprite& getSprite();
    Vec2 getScale();
};
