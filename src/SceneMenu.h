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
    int menuIndex = 0;

    // TODO: load from Assets
    sf::Font m_font;
    bool m_start = false;

    void init();

public:
    SceneMenu(GameEngine* gameEngine);

    void update();

    void sRender();

    // Scene を介して継承されました
    virtual void onEnd() override;
    virtual void sDoAction(const Action& action) override;
};
