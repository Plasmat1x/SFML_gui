#include "Scene2.h"

#include <sstream>

SceneOptions::SceneOptions(Engine* engine)
{
    init(engine);

    res_iter = 0;

    res.push_back(sf::Vector2f(800.0f, 600.0f));
    res.push_back(sf::Vector2f(1280.0f, 1024.0f));
    res.push_back(sf::Vector2f(1920.0f, 1080.0f));
}

void SceneOptions::init(Engine* engine)
{
    this->engine = engine;
    this->event = &engine->events;
    this->view = &engine->view;

    sf::Vector2f pos = sf::Vector2f(this->engine->window.getSize());
    this->view->setSize(pos);
    pos *= 0.5f;
    this->view->setCenter(pos);;

    this->buff << view->getSize().x << "x" << view->getSize().y << std::flush;

    font.loadFromFile("../res/fonts/MorrisRomanBlack.ttf");
    this->fonts["main_font"] = font;

    this->style["button"] = GuiStyle(&this->fonts.at("main_font"), 1,
        sf::Color(0xc6, 0xc6, 0xc6, 0xff), sf::Color(0x94, 0x94, 0x94, 0xff), sf::Color(0xff, 0xff, 0x66, 0xff),
        sf::Color(0xc6, 0xc6, 0xc6, 0xff), sf::Color(0x94, 0x94, 0x94, 0xff), sf::Color(0xff, 0x66, 0x66, 0xff));
    this->style["text"] = GuiStyle(&this->fonts.at("main_font"), 0,
        sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0xff, 0xff, 0xff, 0xff),
        sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0xff, 0xff, 0xff, 0xff));

    this->guiSystem.emplace("save", Gui(sf::Vector2f(192, 32),
        4,
        false,
        this->style.at("button"),
        { std::make_pair("Save", "save_state") }));
    this->guiSystem.at("save").setPosition(pos);
    this->guiSystem.at("save").setOrigin(96, 32 * 0.5f);
    this->guiSystem.at("save").show();

    this->guiSystem.emplace("back", Gui(sf::Vector2f(192, 32),
        4,
        false,
        this->style.at("button"),
        { std::make_pair("Back", "back_state") }));
    this->guiSystem.at("back").setPosition(this->guiSystem.at("save").getPosition() + sf::Vector2f(0, 42));
    this->guiSystem.at("back").setOrigin(96, 32 * 0.5f);
    this->guiSystem.at("back").show();

    this->guiSystem.emplace("res", Gui(sf::Vector2f(192, 32),
        4,
        false,
        this->style.at("text"),
        { std::make_pair("Resolution", "__res") }));
    this->guiSystem.at("res").setPosition(this->guiSystem.at("back").getPosition() + sf::Vector2f(-96, 42));
    this->guiSystem.at("res").setOrigin(96, 32 * 0.5f);
    this->guiSystem.at("res").show();

    this->guiSystem.emplace("resolution", Gui(sf::Vector2f(192, 32),
        4,
        false,
        this->style.at("button"),
        { std::make_pair(buff.str(), "resolution") }));
    this->guiSystem.at("resolution").setPosition(this->guiSystem.at("back").getPosition() + sf::Vector2f(106, 42));
    this->guiSystem.at("resolution").setOrigin(96, 32 * 0.5f);
    this->guiSystem.at("resolution").show();


    /* //this part seems like contex menu
    this->guiSystem.emplace(
        "resolution",
        Gui(sf::Vector2f(192, 32),
            4,
            false,
            this->style.at("button"),
            {
                std::make_pair(buff.str(), "resolution"),
                std::make_pair("some1", "some_one"),
                std::make_pair("some2", "some_two"),
            }));
    this->guiSystem.at("resolution").setPosition(this->guiSystem.at("back").getPosition() + sf::Vector2f(106, 42));
    this->guiSystem.at("resolution").setOrigin(96, 32 * 0.5f);
    this->guiSystem.at("resolution").show();
    */
}

void SceneOptions::processInput()
{
    sf::Vector2f mousePos = this->engine->window.mapPixelToCoords(
        sf::Mouse::getPosition(this->engine->window), *this->view);

    res_txt = buff.str();
    this->guiSystem.at("resolution").setEntryText(0, res_txt);
    this->buff.clear();

    while (this->engine->window.pollEvent(*event))
    {
        switch (this->engine->events.type)
        {
        case sf::Event::Closed:
        {
            engine->window.close();
            break;
        }
        case sf::Event::KeyPressed:
        {
            if (this->engine->events.key.code == sf::Keyboard::Escape)
            {
                this->engine->_pop();
                return;
            }
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            if (this->engine->events.mouseButton.button == sf::Mouse::Left)
            {
                for (auto const& [key, val] : guiSystem)
                {
                    std::string msg = this->guiSystem.at(key).activate(mousePos);

                    if (msg == "save_state")
                    {
                        std::cout << "next state menu with new param" << std::endl;
                        this->engine->_pop();
                        return;
                    }

                    if (msg == "back_state")
                    {
                        std::cout << "next state menu without new param" << std::endl;
                        this->engine->_pop();
                        return;
                    }

                    if (msg == "resolution")
                    {

                    }
                }
            }
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            if (this->engine->events.mouseButton.button == sf::Mouse::Left)
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
        case sf::Event::Resized:
        {
            this->view->setSize(this->engine->events.size.width, this->engine->events.size.height);
            sf::Vector2f pos = sf::Vector2f(this->engine->events.size.width, this->engine->events.size.height);
            pos *= 0.5f;
            pos = this->engine->window.mapPixelToCoords(sf::Vector2i(pos), *this->view);
            this->guiSystem.at("save").setPosition(pos);

            this->buff << view->getSize().x << "x" << view->getSize().y << std::flush;
            break;
        }
        default: break;
        }
    }
}

void SceneOptions::update(const float dt)
{
    
}

void SceneOptions::render(const float dt)
{
    this->engine->window.setView(*view);
    this->engine->window.clear(sf::Color::Cyan);
    //render gui
    for (auto gui : this->guiSystem)this->engine->window.draw(gui.second);

    return;
}

void SceneOptions::cleanup()
{

}
