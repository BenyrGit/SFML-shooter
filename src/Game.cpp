#include "Game.hpp"

Game::Game()
    : mWindow(sf::VideoMode({ 1024u, 768u }), "SFML Shooter")
    , mPlayerShape(40.f)
{
    mWindow.setFramerateLimit(60);

    mPlayerShape.setFillColor(sf::Color::Cyan);
    mPlayerShape.setPosition({ 200.f, 150.f });
}

void Game::run()
{
    while (mWindow.isOpen())
    {
        processEvents();
        update();
        render();
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
    }
}

void Game::update()
{}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mPlayerShape);
    mWindow.display();
}