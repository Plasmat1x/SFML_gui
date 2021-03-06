#include "ResourceManager.h"

std::map<std::string, sf::Image> ResourceManager::images;
std::map<std::string, sf::Font>  ResourceManager::fonts;

sf::Image ResourceManager::loadImage(std::string key_name, std::string file_name)
{
    sf::Image image;
    std::string path = "../res/img/";
    
    image.loadFromFile(path + file_name);
    
    images[key_name] = image;
    return images[key_name];
}

sf::Image ResourceManager::getImage(std::string key_name)
{
    return images[key_name];
}

sf::Font ResourceManager::loadFont(std::string key_name, std::string file_name)
{
    sf::Font font;
    std::string path = "../res/fonts/";

    font.loadFromFile(path + file_name);

    fonts[key_name] = font;
    return fonts[key_name];
}

sf::Font ResourceManager::getFont(std::string key_name)
{
    return fonts[key_name];
}

void ResourceManager::cleanup()
{
}
