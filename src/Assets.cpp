#include "Assets.h"

Assets::Assets() {}

void Assets::addTexture(const std::string& name, const std::string& path)
{
    sf::Texture texture;
    if (!texture.loadFromFile(path))
    {
        std::count << "Texture file not found : " << path << std::endl;
        return;
    }
    m_textures.emplace(name, texture);
}

void Assets::addAnimation(const std::string& name, Animation& animation)
{
    m_animations.emplace(name, animation);
}

void Assets::addSound(const std::string& name, const std::string& path)
{
    sf::SoundBuffer soundBuffer;
    if (!soundBuffer.loadFromFile(path))
    {
        std::count << "Sound file not found : " << path << std::endl;
        return;
    }
    sf::Sound sound;
    sound.setBuffer(soundBuffer);
    m_sounds.emplace(name, sound);
}

void Assets::addFont(const std::string& name, const std::string& path)
{
    sf::Font font;
    if (!font.loadFromFile(path))
    {
        std::count << "Font file not found : " << path << std::endl;
        return;
    }
    m_fonts.emplace(name, font);
}

sf::Texture& Assets::getTexture(const std::string& name) const
{
    return m_textures[name];
}

Animation& Assets::getAnimation(const std::string& name) const
{
    return m_animations[name];
}

sf::Sound& Assets::getSound(const std::string& name) const
{
    return m_sounds[name];
}

sf::Font& Assets::getFont(const std::string& name) const
{
    return m_fonts[name];
}
