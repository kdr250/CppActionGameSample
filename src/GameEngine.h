#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>
#include "asset/Assets.h"
#include "scene/Scene.h"

typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

class GameEngine
{
protected:
    sf::RenderWindow m_window;
    Assets m_assets;
    std::string m_currentScene;
    SceneMap m_sceneMap;
    size_t m_simulationSpeed = 1;
    bool m_running           = true;
    bool m_screenshot        = false;

    void init(const std::string& path);
    void update();

    void sUserInput();

    std::shared_ptr<Scene> currentScene();

public:
    GameEngine(const std::string& path);

    void changeScene(const std::string& sceneName,
                     std::shared_ptr<Scene> scene,
                     bool endCurrentScene = false);

    void run();
    void quit();

    sf::RenderWindow& window();
    Assets& getAssets();
    bool isRunning();
    void takeScreenshot();
};
