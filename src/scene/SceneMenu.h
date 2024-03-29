#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "../action/Action.h"
#include "Scene.h"

class SceneMenu : public Scene
{
protected:
    std::vector<sf::Text> m_menuTexts;

    bool m_start = false;
    bool m_quit  = false;

    void init();

public:
    SceneMenu(GameEngine* gameEngine);

    void update();

    void sRender();

    // Scene を介して継承されました
    virtual void onEnd() override;
    virtual void sDoAction(const Action& action) override;
};
