#include "Player.hpp"
#include "Aircraft.hpp"

namespace
{
    void accelerateAircraft(Aircraft& aircraft, sf::Vector2f direction, sf::Time Time)
    {
        const float speed = aircraft.getMaxSpeed();

        aircraft.accelerate({
            direction.x * speed,
            direction.y * speed
            });
    }
}

Player::Player()
{
    initializeKeyBindings();
    initializeActions();
}

// derivedAction vient de Command.hpp
// La fonction lie le comportement avec une action et définie leur categorie à Aircraft
void Player::initializeActions()
{
    mActionBinding[Action::MoveLeft].action =
        derivedAction<Aircraft>(
            [](Aircraft& aircraft, sf::Time deltaTime)   
            {
                accelerateAircraft(aircraft, { -1.f, 0.f }, deltaTime);
            }
        );

    mActionBinding[Action::MoveRight].action =
        derivedAction<Aircraft>(
            [](Aircraft& aircraft, sf::Time deltaTime)
            {
                accelerateAircraft(aircraft, { 1.f, 0.f }, deltaTime);
            }
        );

    mActionBinding[Action::MoveUp].action =
        derivedAction<Aircraft>(
            [](Aircraft& aircraft, sf::Time deltaTime)
            {
                accelerateAircraft(aircraft, { 0.f, -1.f }, deltaTime);
            }
        );

    mActionBinding[Action::MoveDown].action =
        derivedAction<Aircraft>(
            [](Aircraft& aircraft, sf::Time deltaTime)
            {
                accelerateAircraft(aircraft, { 0.f, 1.f }, deltaTime);
            }
        );

    mActionBinding[Action::Fire].action =
        derivedAction<Aircraft>(
            [](Aircraft& aircraft, sf::Time deltaTime)
            {
                aircraft.fire();
            }
        );

    mActionBinding[Action::LaunchMissile].action =
        derivedAction<Aircraft>(
            [](Aircraft& aircraft, sf::Time deltaTime)
            {
                aircraft.launchMissile();
            }
        );

    for (auto& pair : mActionBinding)
    {
        pair.second.category = Category::PlayerAircraft;
    }
}

void Player::initializeKeyBindings()
{
    mKeyBinding[sf::Keyboard::Key::A] = Action::MoveLeft;
    mKeyBinding[sf::Keyboard::Key::Left] = Action::MoveLeft;

    mKeyBinding[sf::Keyboard::Key::D] = Action::MoveRight;
    mKeyBinding[sf::Keyboard::Key::Right] = Action::MoveRight;

    mKeyBinding[sf::Keyboard::Key::W] = Action::MoveUp;
    mKeyBinding[sf::Keyboard::Key::Up] = Action::MoveUp;

    mKeyBinding[sf::Keyboard::Key::S] = Action::MoveDown;
    mKeyBinding[sf::Keyboard::Key::Down] = Action::MoveDown;

    mKeyBinding[sf::Keyboard::Key::Space] = Action::Fire;
    mKeyBinding[sf::Keyboard::Key::M] = Action::LaunchMissile;
}

// Les déplacements sont envoyées tant que la touche est maintenue
bool Player::isRealtimeAction(Action action)
{
    switch (action)
    {
    case Action::MoveLeft:
    case Action::MoveRight:
    case Action::MoveUp:
    case Action::MoveDown:
        return true;

    case Action::Fire:
    case Action::LaunchMissile:
        return false;
    }

    return false;
}

// fonction pour gérer les actions ponctuelles
void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        // On vérifie si la touche pressée est associées à une action
        const auto found = mKeyBinding.find(keyPressed->code);

        //                                et que l'action est ponctuelle
        if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
        {
            commands.push(mActionBinding[found->second]);
        }
    }
}

// fonction pour gérer les actions continues : déplacements
void Player::handleRealtimeInput(CommandQueue& commands)
{
    for (const auto& pair : mKeyBinding)
    {
        const sf::Keyboard::Key key = pair.first;
        const Action action = pair.second;

        if (sf::Keyboard::isKeyPressed(key) && isRealtimeAction(action))
        {
            commands.push(mActionBinding[action]);
        }
    }
}

// Permet d'assigner une touche à une action
void Player::assignKey(Action action, sf::Keyboard::Key key)
{
    for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end();)
    {
        // retire les touches associées à l'action en paramètre
        if (itr->second == action)
        {
            itr = mKeyBinding.erase(itr);
        }
        else
        {
            ++itr;
        }
    }

    // assigne la nouvelle touche
    mKeyBinding[key] = action;
}

// Retourne la première touche trouvée pour une action
sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
    for (const auto& pair : mKeyBinding)
    {
        if (pair.second == action)
        {
            return pair.first;
        }
    }

    return sf::Keyboard::Key::Unknown;
}

void Player::resetKeyBindings()
{
    mKeyBinding.clear();
    initializeKeyBindings();
}