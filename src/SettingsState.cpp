#include "SettingsState.hpp"
#include "Label.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

SettingsState::SettingsState(StateStack& stack, Context context)
    : State(stack, context)
    , mGUIContainer()
    , mBindingButtons()
    , mBindingActions({
        Player::Action::MoveLeft,
        Player::Action::MoveRight,
        Player::Action::MoveUp,
        Player::Action::MoveDown
        })
{
    const sf::Font& font = context.fonts->get(Fonts::ID::Main);
    const sf::Vector2f viewSize = context.window->getDefaultView().getSize();

    mGUIContainer.setPosition({
        viewSize.x / 2.f,
        viewSize.y / 2.f
        });

    auto titleLabel = std::make_unique<GUI::Label>(
        "Configuration des touches",
        font,
        40
    );
    titleLabel->setPosition({ 0.f, -230.f });

    mGUIContainer.pack(std::move(titleLabel));

    const std::array<std::string, 4> actionNames{
        "Gauche",
        "Droite",
        "Haut",
        "Bas"
    };

    for (std::size_t i = 0; i < mBindingButtons.size(); ++i)
    {
        auto button = std::make_unique<GUI::Button>(font);

        button->setPosition({
            0.f,
            -140.f + static_cast<float>(i) * 70.f
            });

        mBindingButtons[i] = button.get();

        button->setCallback([this, i]()
            {
                mIsBinding = true;
                mActionBindingIndex = i;

                mBindingButtons[i]->setText("Appuie sur une touche...");
            });

        mGUIContainer.pack(std::move(button));
    }

    auto resetButton = std::make_unique<GUI::Button>(font);
    resetButton->setPosition({ 0.f, 150.f });
    resetButton->setText("Réinitialiser");
    resetButton->setCallback([this]()
        {
            getContext().player->resetKeyBindings();
            updateLabels();
        });


    auto backButton = std::make_unique<GUI::Button>(font);
    backButton->setPosition({ 0.f, 230.f });
    backButton->setText("Retour");
    backButton->setCallback([this]()
    {
        requestStackPop();
        requestStackPush(States::ID::Menu);
    });

    mGUIContainer.pack(std::move(resetButton));
    mGUIContainer.pack(std::move(backButton));

    updateLabels();
}

void SettingsState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());
    window.draw(mGUIContainer);
}

bool SettingsState::update(sf::Time)
{
    return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
    if (mIsBinding)
    {
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Escape)
            {
                mIsBinding = false;
                updateLabels();

                return false;
            }

            if (isBindingKeyAllowed(keyPressed->code))
            {
                getContext().player->assignKey(
                    mBindingActions[mActionBindingIndex],
                    keyPressed->code
                );

                mIsBinding = false;
                updateLabels();
            }
        }

        return false;
    }

    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->code == sf::Keyboard::Key::Escape)
        {
            requestStackPop();
            requestStackPush(States::ID::Menu);
            return false;
        }
    }

    mGUIContainer.handleEvent(event);

    return false;
}

void SettingsState::updateLabels()
{
    const std::array<std::string, 4> actionNames{
        "Gauche",
        "Droite",
        "Haut",
        "Bas"
    };

    for (std::size_t i = 0; i < mBindingButtons.size(); ++i)
    {
        const sf::Keyboard::Key key =
            getContext().player->getAssignedKey(mBindingActions[i]);

        mBindingButtons[i]->setText(
            actionNames[i] + " : " + toString(key)
        );
    }
}

bool SettingsState::isBindingKeyAllowed(sf::Keyboard::Key key) const
{
    switch (key)
    {
    case sf::Keyboard::Key::Unknown:
    case sf::Keyboard::Key::Enter:
    case sf::Keyboard::Key::Escape:
        return false;

    default:
        return true;
    }
}