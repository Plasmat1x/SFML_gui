#pragma once
#include <vector>

#include "Engine.h"
#include "Scene.h"
#include "Gui.h"

#include "imgui/imgui.h"
#include "imgui-sfml/imgui-SFML.h"

class SceneOne :
    public Scene
{
public:

    SceneOne(Engine* engine);

    void init(Engine* engine);
    void processInput();
    void update(const float dt);
    void render(const float dt);
    void cleanup();

private:

    std::map<std::string, Gui> guiSystem;
    std::map<std::string, GuiStyle> style;
    std::map<std::string, sf::Font> fonts;
    sf::Font font;
};

