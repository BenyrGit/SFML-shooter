#include "Game.hpp"
#include <stdexcept>
#include <string>

// permet de déclarer des fonctions et variables locale. Temporaire
namespace
{
    constexpr float PlayerSpeed = 300.f;
}

Game::Game()
    : mWindow(sf::VideoMode({ 1024u, 768u }), "SFML Shooter")
    ,mWorld(mWindow)
{
    mWindow.setFramerateLimit(60);
}

void Game::run()
{
    // temps du jeu = 1/60 seconde
    constexpr sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    // chronomètre + temps accumulé 
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {

        timeSinceLastUpdate += clock.restart();
        
        // pour l'instant le jeu rattrape tout le temps en retard en un seul coup avant de faire un render()
        while (timeSinceLastUpdate >= TimePerFrame) 
        {
            timeSinceLastUpdate -= TimePerFrame;

            processEvents();

            if (!mWindow.isOpen())
            {
                return;
            }

            update(TimePerFrame);
        }

        if (mWindow.isOpen())
        {
            render();
        }
    }
}

void Game::processEvents()
{
    while (const std::optional event = mWindow.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            mWindow.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            handlePlayerInput(keyPressed->code, true);
        } 
        else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
        {
            handlePlayerInput(keyReleased->code, false);
        }
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::Key::Escape && isPressed)
    {
        mWindow.close();
    }
    else if (key == sf::Keyboard::Key::W  || key == sf::Keyboard::Key::Up)
    {
        mIsMovingUp = isPressed;
    }
    else if (key == sf::Keyboard::Key::S || key == sf::Keyboard::Key::Down)
    {
        mIsMovingDown = isPressed;
    }
    else if (key == sf::Keyboard::Key::A || key == sf::Keyboard::Key::Left)
    {
        mIsMovingLeft = isPressed;
    }
    else if (key == sf::Keyboard::Key::D || key == sf::Keyboard::Key::Right)
    {
        mIsMovingRight = isPressed;
    } 
}

void Game::update(sf::Time deltaTime)
{
    sf::Vector2f movement{ 0.f, 0.f };

    if (mIsMovingUp)
    {
        movement.y -= PlayerSpeed;
    }

    if (mIsMovingDown)
    {
        movement.y += PlayerSpeed;
    }

    if (mIsMovingLeft)
    {
        movement.x -= PlayerSpeed;
    }

    if (mIsMovingRight)
    {
        movement.x += PlayerSpeed;
    }

    mWorld.handlePlayerMovement(movement, deltaTime);
    mWorld.update(deltaTime);
}

void Game::render()
{
    mWindow.clear();
    mWorld.draw();
    mWindow.display();
}

