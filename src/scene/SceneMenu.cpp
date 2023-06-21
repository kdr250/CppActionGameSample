#include "SceneMenu.h"
#include <iostream>
#include "../GameEngine.h"
#include "ScenePlay.h"

void SceneMenu::init()
{
    auto& fontBold  = m_game->getAssets().getFont("FontRobotoBold");
    auto& fontLight = m_game->getAssets().getFont("FontRobotoLight");

    sf::Text titleText;
    titleText.setFont(fontBold);
    titleText.setCharacterSize(72);
    titleText.setFillColor(sf::Color::Black);
    titleText.setStyle(sf::Text::Style::Bold);
    titleText.setString("Sample Adventure");
    titleText.setOrigin(titleText.getGlobalBounds().width / 2,
                        titleText.getGlobalBounds().height / 2);
    titleText.setPosition(m_game->window().getSize().x / 2, m_game->window().getSize().y / 2 - 200);
    m_menuTexts.push_back(titleText);

    sf::Text menuText;
    menuText.setFont(fontBold);
    menuText.setCharacterSize(56);
    menuText.setFillColor(sf::Color::White);
    menuText.setString("Press Enter to Start!");
    menuText.setOrigin(menuText.getGlobalBounds().width / 2, menuText.getGlobalBounds().height / 2);
    menuText.setPosition(m_game->window().getSize().x / 2, m_game->window().getSize().y / 2);
    m_menuTexts.push_back(menuText);

    sf::Text menuText2;
    menuText2.setFont(fontLight);
    menuText2.setCharacterSize(48);
    menuText2.setFillColor(sf::Color::Black);
    menuText2.setString("UP:W  LEFT:A  RIGHT:D  SHOOT:SPACE  BACK:ESC");
    menuText2.setOrigin(menuText2.getGlobalBounds().width / 2,
                        menuText2.getGlobalBounds().height / 2);
    menuText2.setPosition(m_game->window().getSize().x / 2, m_game->window().getSize().y - 100);
    m_menuTexts.push_back(menuText2);

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
    m_game->window().clear(sf::Color(100, 100, 255));
    for (auto& text : m_menuTexts)
    {
        m_game->window().draw(text);
    }
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
