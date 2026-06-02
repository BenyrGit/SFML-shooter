#include "Game.hpp"

Game::Game()
    : mWindow(sf::VideoMode({ 800u, 600u }), "SFML Game Development - Chapter 1")
    , mPlayer(40.f)
{
    mWindow.setFramerateLimit(60);

    mPlayer.setFillColor(sf::Color::Cyan);
    mPlayer.setPosition({ 100.f, 100.f });
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
    mWindow.draw(mPlayer);
    mWindow.display();
}