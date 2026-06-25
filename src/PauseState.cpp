#include "PauseState.hpp"
#include "Button.hpp"
#include "Label.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

PauseState::PauseState(StateStack& stack, Context context)
    : State(stack, context)
    , mBackgroundShape()
    , mGuiContainer()
{
    const sf::Vector2f viewSize = context.window->getDefaultView().getSize();
    const sf::Font& font = context.fonts->get(Fonts::ID::Main);

    mBackgroundShape.setSize(viewSize);
    mBackgroundShape.setFillColor(sf::Color(0, 0, 0, 150));                     //fond semi-transparent, permet de voir GameState

    mGuiContainer.setPosition({
        viewSize.x / 2.f,
        viewSize.y / 2.f
    });

    auto pauseLabel = std::make_unique<GUI::Label>(
        "Pause",
        font,
        60
    );

    pauseLabel->setPosition({ 0.f, -140.f });

    auto resumeButton = std::make_unique<GUI::Button>(font);
    resumeButton->setPosition({ 0.f, -30.f });
    resumeButton->setText("Reprendre");
    resumeButton->setCallback([this]()
    {
        requestStackPop();
    });

    auto menuButton = std::make_unique<GUI::Button>(font);
    menuButton->setPosition({ 0.f, 50.f });
    menuButton->setText("Menu principal");
    menuButton->setCallback([this]()
    {
        requestStateClear();
        requestStackPush(States::ID::Menu);
    });

    mGuiContainer.pack(std::move(pauseLabel));
    mGuiContainer.pack(std::move(resumeButton));
    mGuiContainer.pack(std::move(menuButton));
}

void PauseState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    window.draw(mBackgroundShape);
    window.draw(mGuiContainer);
}

bool PauseState::update(sf::Time)
{
    return false;                                                            // On empèche le GameState de se mettre à jour
}

bool PauseState::handleEvent(const sf::Event& event)
{
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->code == sf::Keyboard::Key::Escape)
        {
            requestStackPop();
            return false;
        }
    }

    mGuiContainer.handleEvent(event);

    return false;
}