#include "LoadingState.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

LoadingState::LoadingState(StateStack& stack, Context context)
    : State(stack, context)
    , mLoadingText(context.fonts->get(Fonts::ID::Main), "Chargement...", 45)
{
    const sf::Vector2f viewSize = context.window->getDefaultView().getSize();

    centerOrigin(mLoadingText);
    mLoadingText.setPosition({
        viewSize.x / 2.f,
        viewSize.y / 2.f
        });
}

void LoadingState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());
    window.draw(mLoadingText);
}

bool LoadingState::update(sf::Time)
{
    if (!mGameStateCreated)
    {
        mGameStateCreated = true;

        requestStackPop();
        requestStackPush(States::ID::Game);
    }

    return true;
}

bool LoadingState::handleEvent(const sf::Event&)
{
    return true;
}