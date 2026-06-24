#include "MenuState.hpp"
#include "Button.hpp"
#include "ResourceTypes.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context)
    , mGUIContainer()
{
    const sf::Font& font = context.fonts->get(Fonts::ID::Main);
    const sf::Vector2f viewSize = context.window->getView().getSize();

    mGUIContainer.setPosition({
        viewSize.x / 2.f,
        viewSize.y / 2.f
        });

    auto playButton = std::make_unique<GUI::Button>(font);
    playButton->setPosition({ 0.f, -45.f });
    playButton->setText("Jouer");
    playButton->setCallback([this]()
    {
        requestStackPop();
        requestStackPush(States::ID::Loading);
    });

    auto exitButton = std::make_unique<GUI::Button>(font);
    exitButton->setPosition({ 0.f, 45.f });
    exitButton->setText("Quitter");
    exitButton->setCallback([this]()
    {
        requestStateClear();
    });

    mGUIContainer.pack(std::move(playButton));
    mGUIContainer.pack(std::move(exitButton));
}

void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());
    window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time)
{
    return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->code == sf::Keyboard::Key::Escape)
        {
            requestStateClear();
            return false;
        }
    }

    mGUIContainer.handleEvent(event);

    return true;
}