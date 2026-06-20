#include "MenuState.hpp"

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

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context)
{
    const sf::Font& font = context.fonts->get(Fonts::ID::Main);
    const sf::Vector2f viewSize = context.window->getView().getSize();

    sf::Text playOption(font, "Jouer", 40);
    centerOrigin(playOption);
    playOption.setPosition({
        viewSize.x / 2.f,
        viewSize.y / 2.f - 40.f
        });

    sf::Text exitOption(font, "Quitter", 40);
    centerOrigin(exitOption);
    exitOption.setPosition({
        viewSize.x / 2.f,
        viewSize.y / 2.f + 40.f
        });

    mOptions.push_back(playOption);
    mOptions.push_back(exitOption);

    updateOptionText();
}

void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    for (const sf::Text& option : mOptions)
    {
        window.draw(option);
    }
}

bool MenuState::update(sf::Time)
{
    return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->code == sf::Keyboard::Key::Up)
        {
            if (mOptionIndex > 0)
            {
                --mOptionIndex;
            }
            else
            {
                mOptionIndex = mOptions.size() - 1;
            }

            updateOptionText();
        }
        else if (keyPressed->code == sf::Keyboard::Key::Down)
        {
            mOptionIndex = (mOptionIndex + 1) % mOptions.size();

            updateOptionText();
        }
        else if (keyPressed->code == sf::Keyboard::Key::Enter)
        {
            if (mOptionIndex == 0)
            {
                requestStackPop();
                requestStackPush(States::ID::Game);
            }
            else if (mOptionIndex == 1)
            {
                requestStateClear();
            }
        }
        else if (keyPressed->code == sf::Keyboard::Key::Escape)
        {
            requestStateClear();
        }
    }

    return true;
}

void MenuState::updateOptionText()
{
    for (sf::Text& option : mOptions)
    {
        option.setFillColor(sf::Color::White);
    }

    mOptions[mOptionIndex].setFillColor(sf::Color::Yellow);
}