#include "GameEngine.h"
#include <iostream>
#include "SceneMenu.h"

void GameEngine::init(const std::string& path)
{
    // TODO: comment out for test
    //m_assets.loadFromFile(path);

    m_window.create(sf::VideoMode(1280, 768), "Action Game");
    m_window.setFramerateLimit(60);

    changeScene("MENU", std::make_shared<SceneMenu>(this));
}

void GameEngine::update()
{
    m_window.clear();
    sUserInput();
    currentScene()->update();
    currentScene()->sRender();
    m_window.display();
}

void GameEngine::sUserInput()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            quit();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::X)
            {
                std::cout << "try to save screenshot" << std::endl;
                sf::Texture texture;
                texture.create(m_window.getSize().x, m_window.getSize().y);
                texture.update(m_window);
                if (texture.copyToImage().saveToFile("test.png"))
                {
                    std::cout << "screenshot saved to test.png" << std::endl;
                }
            }
        }

        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
        {
            if (currentScene()->getActionMap().find(event.key.code)
                == currentScene()->getActionMap().end())
            {
                continue;
            }

            const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";

            currentScene()->doAction(
                Action(currentScene()->getActionMap().at(event.key.code), actionType));
        }
    }
}

std::shared_ptr<Scene> GameEngine::currentScene()
{
    return m_sceneMap[m_currentScene];
}

GameEngine::GameEngine(const std::string& path)
{
    init(path);
}

void GameEngine::changeScene(const std::string& sceneName,
                             std::shared_ptr<Scene> scene,
                             bool endCurrentScene)
{
    m_currentScene = sceneName;
    if (endCurrentScene)
    {
        m_sceneMap.erase(m_currentScene);
    }
    m_sceneMap[sceneName] = scene;
}

void GameEngine::run()
{
    while (isRunning())
    {
        update();
    }
}

void GameEngine::quit()
{
    m_running = false;
}

sf::RenderWindow& GameEngine::window()
{
    return m_window;
}

Assets& GameEngine::getAssets()
{
    return m_assets;
}

bool GameEngine::isRunning()
{
    return m_running && m_window.isOpen();
}
