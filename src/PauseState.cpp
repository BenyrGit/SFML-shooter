#include "PauseState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace
{
    void centerOrigin(sf::Text& text)
    {
        const sf::FloatRect bounds = text.getLocalBounds();

        text.setOrigin({
            bounds.position.x + bounds.size.x / 2.f,
            bounds.position.y + bounds.size.y / 2.f
            });
    }
}

PauseState::PauseState(StateStack& stack, Context context)
    : State(stack, context)
    , mBackgroundShape()
    , mPausedText(context.fonts->get(Fonts::ID::Main), "Pause", 70)
    , mInstructionText(
        context.fonts->get(Fonts::ID::Main),
        "Appuie sur Echap pour reprendre\nAppuie sur Retour pour retourner au menu",
        28
    )
{
    const sf::Vector2f viewSize = context.window->getDefaultView().getSize();

    mBackgroundShape.setSize(viewSize);
    mBackgroundShape.setFillColor(sf::Color(0, 0, 0, 150));

    centerOrigin(mPausedText);
    mPausedText.setPosition({
        viewSize.x / 2.f,
        viewSize.y / 2.f - 80.f
        });

    centerOrigin(mInstructionText);
    mInstructionText.setPosition({
        viewSize.x / 2.f,
        viewSize.y / 2.f + 60.f
        });
}

void PauseState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    window.draw(mBackgroundShape);
    window.draw(mPausedText);
    window.draw(mInstructionText);
}

bool PauseState::update(sf::Time)
{
    return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->code == sf::Keyboard::Key::Escape)
        {
            requestStackPop();
        }
        else if (keyPressed->code == sf::Keyboard::Key::Backspace)
        {
            requestStateClear();
            requestStackPush(States::ID::Menu);
        }
    }

    return false;
}