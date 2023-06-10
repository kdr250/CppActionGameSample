#include "Assets.h"
#include <iostream>

Assets::Assets() {}

void Assets::loadFromFile(const std::string path)
{
    addTexture("Run", "resources/texture/player_run.png");
    Animation animation("Run", m_textures["Run"], 8, 15);
    addAnimation(animation.getName(), animation);

    addTexture("Air", "resources/texture/player_jump.png");
    Animation animation2("Air", m_textures["Air"], 2, 30);
    addAnimation(animation2.getName(), animation2);

    addTexture("Idle", "resources/texture/player_idle.png");
    Animation animation3("Idle", m_textures["Idle"], 2, 30);
    addAnimation(animation3.getName(), animation3);

    addTexture("Brick", "resources/texture/tile_brick.png");
    Animation animation4("Brick", m_textures["Brick"], 1, 0);
    addAnimation(animation4.getName(), animation4);
}

void Assets::addTexture(const std::string& name, const std::string& path)
{
    sf::Texture texture;
    if (!texture.loadFromFile(path))
    {
        std::cout << "Texture file not found : " << path << std::endl;
        return;
    }
    m_textures.emplace(name, texture);
}

void Assets::addAnimation(const std::string& name, Animation& animation)
{
    m_animations.emplace(name, animation);
}

//void Assets::addSound(const std::string& name, const std::string& path)
//{
//    sf::SoundBuffer soundBuffer;
//    if (!soundBuffer.loadFromFile(path))
//    {
//        std::cout << "Sound file not found : " << path << std::endl;
//        return;
//    }
//    sf::Sound sound;
//    sound.setBuffer(soundBuffer);
//    m_sounds.emplace(name, sound);
//}

void Assets::addFont(const std::string& name, const std::string& path)
{
    sf::Font font;
    if (!font.loadFromFile(path))
    {
        std::cout << "Font file not found : " << path << std::endl;
        return;
    }
    m_fonts.emplace(name, font);
}

sf::Texture& Assets::getTexture(const std::string& name)
{
    return m_textures[name];
}

Animation& Assets::getAnimation(const std::string& name)
{
    return m_animations[name];
}

//sf::Sound& Assets::getSound(const std::string& name)
//{
//    return m_sounds[name];
//}

sf::Font& Assets::getFont(const std::string& name)
{
    return m_fonts[name];
}
