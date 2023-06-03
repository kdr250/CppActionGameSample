#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Action.h"
#include "Scene.h"

class SceneMenu : public Scene
{
protected:
    std::vector<std::string> m_menuStrings;
    sf::Text m_menuText;
    std::vector<std::string> m_levelPath;
    int menuIndex;

    void init();

public:
    SceneMenu(GameEngine* gameEngine);

    void update();

    void sRender();
    void sDoAction(Action& action);
};
