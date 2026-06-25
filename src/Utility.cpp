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

// Affiche les touches
std::string toString(sf::Keyboard::Key key) 
{
    switch (key)
    {
    case sf::Keyboard::Key::A:
        return "A";
    case sf::Keyboard::Key::D:
        return "D";
    case sf::Keyboard::Key::W:
        return "W";
    case sf::Keyboard::Key::S:
        return "S";

    case sf::Keyboard::Key::Left:
        return "Gauche";
    case sf::Keyboard::Key::Right:
        return "Droite";
    case sf::Keyboard::Key::Up:
        return "Haut";
    case sf::Keyboard::Key::Down:
        return "Bas";

    case sf::Keyboard::Key::Space:
        return "Espace";
    case sf::Keyboard::Key::M:
        return "M";
    case sf::Keyboard::Key::Enter:
        return "Entrée";
    case sf::Keyboard::Key::Escape:
        return "Échap";

    default:
        return "Touche inconnue";
    }
}