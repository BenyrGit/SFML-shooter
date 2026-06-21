#include "Utility.hpp"

void centerOrigin(sf::Sprite& sprite)
{
    const sf::FloatRect bounds = sprite.getLocalBounds();

    sprite.setOrigin({
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
        });
}

void centerOrigin(sf::Text& text)
{
    const sf::FloatRect bounds = text.getLocalBounds();

    text.setOrigin({
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
        });
}