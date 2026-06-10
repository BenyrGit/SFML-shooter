#pragma once

#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();

    void run();

private:
    void processEvents();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void update(sf::Time deltaTime);
    void render();

    sf::RenderWindow    mWindow;
    sf::Texture mPlayerTexture;
    sf::Sprite mPlayerSprite;

    bool mIsMovingUp    = false;
    bool mIsMovingDown  = false;
    bool mIsMovingLeft  = false;
    bool mIsMovingRight = false;
};