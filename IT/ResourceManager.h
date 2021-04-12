#pragma once
#include <map>
#include <string>

#include <SFML/Graphics.hpp>

class ResourceManager
{
public:
    static std::map<std::string, sf::Image> images;
    static sf::Image loadImage(std::string key_name, std::string file_name);
    static sf::Image getImage(std::string key_name);

    static std::map<std::string, sf::Font> fonts;
    static sf::Font loadFont(std::string key_name, std::string file_name);
    static sf::Font getFont(std::string key_name);

    static void cleanup();

private:
    ResourceManager() {}
};

