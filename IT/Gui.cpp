#include "Gui.h"

sf::Vector2f Gui::getSize()
{
    return sf::Vector2f(this->dimension.x, this->dimension.y * this->entries.size());
}

int Gui::getEntry(const sf::Vector2f mousePos)
{    if (entries.size() == 0) return -1;
    if (!this->visible) return -1;

    for (int i = 0; i < this->entries.size(); ++i)
    {
        sf::Vector2f point = mousePos;
        point += this->entries[i].shape.getOrigin();
        point -= this->entries[i].shape.getPosition();
        
        if (point.x < 0 || point.x > this->entries[i].shape.getScale().x * this->dimension.x) continue;
        if (point.y < 0 || point.y > this->entries[i].shape.getScale().y * this->dimension.y) continue;
        return i;
    }

    return -1;
}

void Gui::setEntryText(int entry, std::string text)
{
    if (entry >= entries.size() || entry < 0) return;
    entries[entry].text.setString(text);
    return;
}

void Gui::setDimensions(sf::Vector2f dimension)
{
    this->dimension = dimension;
    for (auto& entry : entries)
    {
        entry.shape.setSize(dimension);
        entry.text.setCharacterSize(dimension.y - style.borderSize - padding);
    }
    return;
}

void Gui::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!visible) return;

    for (auto entry : this->entries)
    {
        target.draw(entry.shape);
        target.draw(entry.text);
    }

    return;
}

void Gui::show()
{
    sf::Vector2f offset(0.0f, 0.0f);
    this->visible = true;
    for (auto& entry : this->entries)
    {
        sf::Vector2f origin = this->getOrigin();
        origin -= offset;
        entry.shape.setOrigin(origin);
        entry.text.setOrigin(origin);

        entry.shape.setPosition(this->getPosition());
        entry.text.setPosition(this->getPosition());

        if (this->horizontal) offset.x += this->dimension.x;
        else offset.y += this->dimension.y;

    }

    return;
}

void Gui::hide()
{
    this->visible = false;

    return;
}

void Gui::highlight(const int entry)
{
    for (int i = 0; i < entries.size(); ++i)
    {
        if (i == entry)
        {
            entries[i].shape.setFillColor(style.bodyHighlight);
            entries[i].shape.setOutlineColor(style.borderHighlight);
            entries[i].text.setFillColor(style.textHighlight);
        }
        else
        {
            entries[i].shape.setFillColor(style.bodyColor);
            entries[i].shape.setOutlineColor(style.borderColor);
            entries[i].text.setFillColor(style.textColor);
        }
    }

    return;
}

void Gui::highlight(const sf::Vector2f mousePos)
{
    int entry = this->getEntry(mousePos);
    highlight(entry);
}


std::string Gui::activate(const int entry)
{
    if (entry == -1) return "null";
    return entries[entry].message;
}

std::string Gui::activate(const sf::Vector2f mousePos)
{
    int entry = this->getEntry(mousePos);
    return this->activate(entry);
}
