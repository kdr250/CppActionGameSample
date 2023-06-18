#include "Assets.h"
#include <fstream>
#include <iostream>
#include <sstream>

Assets::Assets() {}

void Assets::loadFromFile(const std::string path)
{
    std::ifstream file;
    file.open(path);
    if (!file.is_open())
    {
        std::cout << "Failed to load config file" << std::endl;
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
        std::stringstream assetStream(line);
        std::string type;
        std::string name;
        assetStream >> type >> name;
        if (type == "Texture")
        {
            std::string path;
            assetStream >> path;
            addTexture(name, path);
        }
        else if (type == "Animation")
        {
            std::string textureName;
            int frameCount;
            int speed;
            float scale;
            assetStream >> textureName >> frameCount >> speed >> scale;
            Animation animation(name, m_textures[textureName], frameCount, speed, scale);
            addAnimation(name, animation);
        }
        std::cout << type << " " << name << " is loaded!" << std::endl;
    }
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
