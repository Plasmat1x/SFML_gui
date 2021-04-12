#include "Scene1.h"
#include "Scene2.h"

#include <iostream>

SceneOne::SceneOne(Engine* engine)
{
    init(engine);
}

void SceneOne::init(Engine* engine)
{
    //core setup
    this->engine = engine;
    this->event = &engine->events;
    this->view = &engine->view;

    sf::Vector2f pos = sf::Vector2f(this->engine->window.getSize());
    this->view->setSize(pos);
    pos *= 0.5f;
    this->view->setCenter(pos);

    font.loadFromFile("../res/fonts/MorrisRomanBlack.ttf");
    this->fonts["main_font"] = font;

    this->style["button"] = GuiStyle(&this->fonts.at("main_font"), 1,
        sf::Color(0xc6, 0xc6, 0xc6, 0xff), sf::Color(0x94, 0x94, 0x94, 0xff), sf::Color(0xff, 0xff, 0x66, 0xff),
        sf::Color(0xc6, 0xc6, 0xc6, 0xff), sf::Color(0x94, 0x94, 0x94, 0xff), sf::Color(0xff, 0x66, 0x66, 0xff));
    this->style["text"] = GuiStyle(&this->fonts.at("main_font"), 0,
        sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0xff, 0xff, 0xff, 0xff),
        sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0xff, 0x00, 0x00, 0x00));

    // cretae gui
    this->guiSystem.emplace("new", Gui(sf::Vector2f(192, 32),
        4,
        false,
        this->style.at("button"),
        { std::make_pair("New game", "new_game") }));
    this->guiSystem.at("new").setPosition(pos);
    this->guiSystem.at("new").setOrigin(96, 32 * 0.5f);
    this->guiSystem.at("new").show();

    this->guiSystem.emplace("options", Gui(sf::Vector2f(192, 32),
        4,
        false,
        this->style.at("button"),
        { std::make_pair("Options", "options_state") }));
    this->guiSystem.at("options").setPosition(this->guiSystem.at("new").getPosition() + sf::Vector2f(0,42));
    this->guiSystem.at("options").setOrigin(96, 32 * 0.5f);
    this->guiSystem.at("options").show();

    this->guiSystem.emplace("exit", Gui(sf::Vector2f(192, 32),
        4,
        false,
        this->style.at("button"),
        { std::make_pair("Exit", "exit_game") }));
    this->guiSystem.at("exit").setPosition(this->guiSystem.at("options").getPosition() + sf::Vector2f(0, 42));
    this->guiSystem.at("exit").setOrigin(96, 32 * 0.5f);
    this->guiSystem.at("exit").show();
}

void SceneOne::processInput()
{
    sf::Vector2f mousePos = this->engine->window.mapPixelToCoords(
        sf::Mouse::getPosition(this->engine->window), *this->view);
    while (this->engine->window.pollEvent(*event))
    {
        switch (event->type)
        {
        case sf::Event::Closed:
        {
            engine->window.close();
            break;
        }
        case sf::Event::Resized:
        {
            this->view->setSize(event->size.width, event->size.height);
            sf::Vector2f pos = sf::Vector2f(event->size.width, event->size.height);
            pos *= 0.5f;
            pos = this->engine->window.mapPixelToCoords(sf::Vector2i(pos), *this->view);
            this->guiSystem.at("new").setPosition(pos);
            break;
        }
        case sf::Event::KeyPressed:
        {
            if (event->key.code == sf::Keyboard::Escape)
            {
                this->engine->window.close();
            }
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            if (event->mouseButton.button == sf::Mouse::Left)
            {
                for (auto const& [key, val] : guiSystem)
                {
                    std::string msg = this->guiSystem.at(key).activate(mousePos);

                    if (msg == "new_game")
                    {
                        std::cout << "next state start" << std::endl;
                    }

                    if (msg == "options_state")
                    {
                        std::cout << "next state options" << std::endl;
                        this->engine->_push(new SceneOptions(engine));
                    }

                    if (msg == "exit_game")
                    {
                        this->engine->window.close();
                    }
                }
            }
            break;
        }
        case sf::Event::MouseButtonPressed:
        {


            if (event->mouseButton.button == sf::Mouse::Left)
            {
                for (auto const& [key, val] : guiSystem)
                {
                    //this->guiSystem.at(key).highlight(mousePos);
                }
            }
            break;
        }
        case sf::Event::MouseMoved:
        {


            for (auto const& [key, val] : guiSystem)
            {
                this->guiSystem.at(key).highlight(mousePos);
            }
            break;
        }
        default: break;
        }
    }
}

void SceneOne::update(const float dt)
{

}

void SceneOne::render(const float dt)
{
    this->engine->window.setView(*this->view);
    this->engine->window.clear(sf::Color::Cyan);
    //render gui
    for (auto gui : this->guiSystem)this->engine->window.draw(gui.second);

    return;
}

void SceneOne::cleanup()
{

}
