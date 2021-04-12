#pragma once
#include <vector>

#include "Engine.h"
#include "Scene.h"
#include "Gui.h"

class SceneOptions :
    public Scene
{
public:
    SceneOptions(Engine* engine);

    void init(Engine* engine);
    void processInput();
    void update(const float dt);
    void render(const float dt);
    void cleanup();

private:
    std::ostringstream buff;
    std::string res_txt;
    std::map<std::string, Gui> guiSystem;
    std::map<std::string, GuiStyle> style;
    std::map<std::string, sf::Font> fonts;
    sf::Font font;
    std::vector<sf::Vector2f> res;


    int res_iter;
};

