#include "Game.hpp"
#include "GameState.hpp"
#include "TitleState.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"
#include <stdexcept>
#include <string>

Game::Game()
    : mWindow(sf::VideoMode({ 1024u, 768u }), "SFML Shooter")
    , mTextures()
    , mFonts()
    , mPlayer()
    , mStateStack(State::Context{
        &mWindow,
        &mTextures,
        &mFonts,
        &mPlayer
    })
{
    // désactive la répittion d'une touche quand maintenue
    mWindow.setKeyRepeatEnabled(false);
    mWindow.setFramerateLimit(60);

    mFonts.load(Fonts::ID::Main, "assets/fonts/OpenSans.ttf");

    registerStates();

    mStateStack.pushState(States::ID::Title);
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

        //donne les événements au stateStack qui les transfère ensuite au autres couches
        mStateStack.handleEvent(*event);
    }
}


void Game::update(sf::Time deltaTime)
{
    mStateStack.update(deltaTime);

    if (mStateStack.isEmpty())
    {
        mWindow.close();
    }
   
}

void Game::render()
{
    mWindow.clear();
    mStateStack.draw();
    mWindow.display();
}

void Game::registerStates()
{
    mStateStack.registerState<TitleState>(States::ID::Title);
    mStateStack.registerState<MenuState>(States::ID::Menu);
    mStateStack.registerState<GameState>(States::ID::Game);
    mStateStack.registerState<PauseState>(States::ID::Pause);
}
