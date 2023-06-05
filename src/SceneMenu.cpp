#include "SceneMenu.h"
#include "GameEngine.h"

void SceneMenu::init()
{
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
