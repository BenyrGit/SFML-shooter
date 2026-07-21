#include "Aircraft.hpp"
#include "DataTables.hpp"
#include "Utility.hpp"
#include <iostream>

namespace
{
    const auto Table = initializeAircraftData();

    std::size_t toIndex(Aircraft::Type type)
    {
        return static_cast<std::size_t>(type);
    }
}

Aircraft::Aircraft(Type type, const TextureHolder& textures)
    : Entity(Table[toIndex(type)].hitpoints)
    , mType(type)
    , mSprite(textures.get(Table[toIndex(type)].texture))
{
    centerOrigin(mSprite);
}

sf::FloatRect Aircraft::getBoundingRect() const
{
    return getWorldTransform().transformRect(mSprite.getLocalBounds());
}

void Aircraft::drawCurrent(
    sf::RenderTarget& target,
    sf::RenderStates states
) const
{
    target.draw(mSprite, states);
}

unsigned int Aircraft::getCategory() const
{
    switch (mType)
    {
    case Type::Eagle:
        return Category::PlayerAircraft;

    case Type::Raptor:
        return Category::AlliedAircraft;
    }

    return Category::None;
}

float Aircraft::getMaxSpeed() const
{
    return Table[toIndex(mType)].speed;
}

void Aircraft::fire() 
{
    mIsFiring = true;
}

void Aircraft::launchMissile() 
{
    mIsLauchingMissile = true;
}

bool Aircraft::isFiring() const
{
    return mIsFiring;
}

bool Aircraft::isLaunchingMissile() const
{
    return mIsLauchingMissile;
}

void Aircraft::resetActions()
{
    mIsFiring = false;
    mIsLauchingMissile = false;
}
