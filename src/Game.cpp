#include "Game.hpp"
#include <stdexcept>
#include <string>

Game::Game()
    : mWindow(sf::VideoMode({ 1024u, 768u }), "SFML Shooter")
    ,mWorld(mWindow)
{
    // désactive la répittion d'une touche quand maintenue
    mWindow.setKeyRepeatEnabled(false);
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
            if (keyPressed->code == sf::Keyboard::Key::Escape)
            {
                mWindow.close();
            }
        } 

        mPlayer.handleEvent(*event, mWorld.getCommandQueue());
    }
}


void Game::update(sf::Time deltaTime)
{
    mPlayer.handleRealtimeInput(mWorld.getCommandQueue());

    mWorld.update(deltaTime);
}

void Game::render()
{
    mWindow.clear();
    mWorld.draw();
    mWindow.display();
}

