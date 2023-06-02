#include "Assets.h"

Assets::Assets() {}

void Assets::addTexture(const std::string& name, const std::string path) {}

void Assets::addAnimation(const std : string& name, Animation& animation) {}

void Assets::addSound(const std::string& name, const std::string path) {}

void Assets::addFont(const std::string& name, const std::string path) {}

sf::Texture& Assets::getTexture(const std::string& name) const
{
    // TODO: return ステートメントをここに挿入します
}

Animation& Assets::getAnimation(const std::string& name) const
{
    // TODO: return ステートメントをここに挿入します
}

sf::Sound& Assets::getSound(const std::string& name) const
{
    // TODO: return ステートメントをここに挿入します
}

sf::Font& Assets::getFont(const std::string& name) const
{
    // TODO: return ステートメントをここに挿入します
}
