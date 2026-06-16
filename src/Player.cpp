#include "Player.hpp"
#include "Aircraft.hpp"

namespace
{
    constexpr float PlayerSpeed = 300.f;

    void moveAircraft(SceneNode& node, sf::Vector2f velocity, sf::Time deltaTime)
    {
        Aircraft& aircraft = static_cast<Aircraft&>(node);

        aircraft.setVelocity(velocity);
    }
}

Player::Player()
{
    mKeyBinding[sf::Keyboard::Key::A] = Action::MoveLeft;
    mKeyBinding[sf::Keyboard::Key::Left] = Action::MoveLeft;

    mKeyBinding[sf::Keyboard::Key::D] = Action::MoveRight;
    mKeyBinding[sf::Keyboard::Key::Right] = Action::MoveRight;

    mKeyBinding[sf::Keyboard::Key::W] = Action::MoveUp;
    mKeyBinding[sf::Keyboard::Key::Up] = Action::MoveUp;

    mKeyBinding[sf::Keyboard::Key::S] = Action::MoveDown;
    mKeyBinding[sf::Keyboard::Key::Down] = Action::MoveDown;

    initializeActions();
}

void Player::initializeActions()
{
    mActionBinding[Action::MoveLeft].action =
        [](SceneNode& node, sf::Time deltaTime)
        {
            moveAircraft(node, { -PlayerSpeed, 0.f }, deltaTime);
        };

    mActionBinding[Action::MoveRight].action =
        [](SceneNode& node, sf::Time deltaTime)
        {
            moveAircraft(node, { PlayerSpeed, 0.f }, deltaTime);
        };

    mActionBinding[Action::MoveUp].action =
        [](SceneNode& node, sf::Time deltaTime)
        {
            moveAircraft(node, { 0.f, -PlayerSpeed }, deltaTime);
        };

    mActionBinding[Action::MoveDown].action =
        [](SceneNode& node, sf::Time deltaTime)
        {
            moveAircraft(node, { 0.f, PlayerSpeed }, deltaTime);
        };

    for (auto& pair : mActionBinding)
    {
        pair.second.category = Category::PlayerAircraft;
    }
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
    // Plus tard : tirer, lancer un missile, pause, etc.
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
    for (const auto& pair : mKeyBinding)
    {
        if (sf::Keyboard::isKeyPressed(pair.first))
        {
            commands.push(mActionBinding[pair.second]);
        }
    }
}