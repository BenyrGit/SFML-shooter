#include "GameState.hpp"
#include "Player.hpp"

GameState::GameState(StateStack& stack, Context context)
    : State(stack, context)
    , mWorld(*context.window)
    , mPlayer(context.player)
{}

void GameState::draw()
{
    mWorld.draw();
}

// return true pour que l'état en dessous soit aussi mit à jour
bool GameState::update(sf::Time deltaTime)
{
    mPlayer->handleRealtimeInput(mWorld.getCommandQueue());

    mWorld.update(deltaTime);

    return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
    mPlayer->handleEvent(event, mWorld.getCommandQueue());

    return true;
}