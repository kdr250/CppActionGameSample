#include "Assets.h"
#include <iostream>

Assets::Assets() {}

void Assets::loadFromFile(const std::string path)
{
    sf::Texture texture;
    if (!texture.loadFromFile(path))
    {
        std::cout << "Failed to load file: " << path << std::endl;
    }
    else
    {
        std::cout << "Success to load file: " << path << std::endl;
    }
    m_textures.emplace("Player", texture);  // TODO: Load from config file

    Animation animation("Stand", texture, 2, 5);
    m_animations.emplace("Stand", animation);
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
