#include "SceneMenu.h"
#include <iostream>
#include "../GameEngine.h"
#include "ScenePlay.h"

void SceneMenu::init()
{
    m_font.loadFromFile("resources/fonts/Roboto-Light.ttf");
    m_menuText.setFont(m_font);
    m_menuText.setCharacterSize(64);
    m_menuText.setFillColor(sf::Color::Blue);
    m_menuText.setString("Press Enter to Start!");
    m_menuText.setPosition(100, 100);

    registerAction(sf::Keyboard::Enter, "PLAY");
    registerAction(sf::Keyboard::Escape, "QUIT");
}

SceneMenu::SceneMenu(GameEngine* gameEngine) : Scene(gameEngine)
{
    init();
}

void SceneMenu::update()
{
    if (m_start)
    {
        m_game->changeScene("PLAY",
                            std::make_shared<ScenePlay>(m_game, "resources/level/level1.txt"));
    }
    if (m_quit)
    {
        onEnd();
    }
}

void SceneMenu::sRender()
{
    m_game->window().draw(m_menuText);
}

void SceneMenu::onEnd()
{
    m_game->quit();
}

void SceneMenu::sDoAction(const Action& action)
{
    if (action.type() == "START")
    {
        if (action.name() == "PLAY")
        {
            m_start = true;
        }
        else if (action.name() == "QUIT")
        {
            m_quit = true;
        }
    }
}
