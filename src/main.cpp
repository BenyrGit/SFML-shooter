#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({ 1024u, 768u }),
        "SFML Shoot-em up"
    );

    window.setFramerateLimit(60);

    sf::CircleShape shape{ 80.f };
    shape.setFillColor(sf::Color::Red);
    shape.setPosition({ 50.f, 50.f });

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    test

    return 0;
}