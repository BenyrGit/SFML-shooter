#include "LoadingState.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

LoadingState::LoadingState(StateStack& stack, Context context)
    : State(stack, context)
    , mLoadingText(context.fonts->get(Fonts::ID::Main), "Chargement...", 45)
    , mProgressBarBackground()
    , mProgressBar()
{
    const sf::Vector2f viewSize = context.window->getDefaultView().getSize();

    centerOrigin(mLoadingText);
    mLoadingText.setPosition({
        viewSize.x / 2.f,
        viewSize.y / 2.f
    });

    mProgressBarBackground.setSize({ 400.f, 20.f });
    mProgressBarBackground.setFillColor(sf::Color(80, 80, 80));
    mProgressBarBackground.setOrigin({
        mProgressBarBackground.getSize().x / 2.f,
        mProgressBarBackground.getSize().y / 2.f
        });
    mProgressBarBackground.setPosition({
        viewSize.x / 2.f,
        viewSize.y / 2.f + 30.f
        });

    mProgressBar.setSize({ 0.f, 20.f });
    mProgressBar.setFillColor(sf::Color::White);
    mProgressBar.setOrigin({
        0.f,
        mProgressBar.getSize().y / 2.f
        });
    mProgressBar.setPosition({
        viewSize.x / 2.f - 200.f,
        viewSize.y / 2.f + 30.f
        });
}

void LoadingState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());
    window.draw(mLoadingText);
    window.draw(mProgressBarBackground);
    window.draw(mProgressBar);
}

bool LoadingState::update(sf::Time deltaTime)
{
    mElapsedTime += deltaTime;

    // pourcentage 
    const float percent = mElapsedTime.asSeconds() / mLoadingDuration.asSeconds();
    setProgress(percent);

    if (!mGameStateCreated && mElapsedTime >= mLoadingDuration)
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

// Mise ;a jour de la barre
void LoadingState::setProgress(float percent)
{

    // On garde la barre entre 0 et 100%
    if (percent < 0.f)
    {
        percent = 0.f;
    }
    else if (percent > 1.f)
    {
        percent = 1.f;
    }

    mProgressBar.setSize({
        400.f * percent,
        mProgressBar.getSize().y
    });

}