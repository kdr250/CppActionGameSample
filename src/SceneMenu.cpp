#include "SceneMenu.h"
#include "GameEngine.h"

void SceneMenu::init()
{
    m_font.loadFromFile("resources/fonts/Roboto-Light.ttf");
    m_menuText.setFont(m_font);
    m_menuText.setCharacterSize(64);
    m_menuText.setFillColor(sf::Color::Blue);
    m_menuText.setString("Hello World!");
    m_menuText.setPosition(100, 100);
}

SceneMenu::SceneMenu(GameEngine* gameEngine) : Scene(gameEngine)
{
    init();
}

void SceneMenu::update() {}

void SceneMenu::sRender()
{
    m_game->window().draw(m_menuText);
}

void SceneMenu::sDoAction(Action& action) {}

void SceneMenu::onEnd() {}

void SceneMenu::sDoAction(const Action& action) {}
