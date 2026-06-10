#pragma once

#include "TextureHolder.hpp"

#include <SFML/Graphics.hpp>
#include <optional>

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
    void keepPlayerInsideWindow();

    sf::RenderWindow            mWindow;
    TextureHolder               mTextures;
    std::optional<sf::Sprite>   mPlayerSprite;  // On utilise optional pour ne pas avoir à construire le sprite avant de charger la texture  

    bool mIsMovingUp    = false;
    bool mIsMovingDown  = false;
    bool mIsMovingLeft  = false;
    bool mIsMovingRight = false;
};