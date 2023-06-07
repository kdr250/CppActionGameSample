#include "Animation.h"

Animation::Animation() {}

Animation::Animation(const std::string& name, const sf::Texture& t) : Animation(name, t, 1, 0) {}

Animation::Animation(const std::string& name, const sf::Texture& t, int frameCount, int speed) :
    m_name(name), m_sprite(t), m_frameCount(frameCount), m_currentFrame(0), m_speed(speed)
{
    m_size = Vec2((float)t.getSize().x / frameCount, (float)t.getSize().y);
    m_sprite.setOrigin(m_size.x / 2.0f, m_size.y / 2.0f);
    m_sprite.setTextureRect(
        sf::IntRect(std::floor(m_currentFrame) * m_size.x, 0, m_size.x, m_size.y));
}

/**
   update the animation to show the next frame, depending on its speed
   animation loops when it reaches the end
*/
void Animation::update()
{
    m_currentFrame++;
    int animationFrame = (m_currentFrame / m_speed) % m_frameCount;
    sf::IntRect rectangle(animationFrame * m_size.x, 0, m_size.x, m_size.y);
    m_sprite.setTextureRect(rectangle);
}

std::string& Animation::getName()
{
    return m_name;
}

Vec2& Animation::getSize()
{
    return m_size;
}

sf::Sprite& Animation::getSprite()
{
    return m_sprite;
}
