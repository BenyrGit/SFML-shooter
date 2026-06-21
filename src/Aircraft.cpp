#include "Aircraft.hpp"
#include "Utility.hpp"
#include <iostream>

namespace
{
    // Convertit l'avion en texture. 
    const sf::Texture& toTexture(Aircraft::Type type, const TextureHolder& textures)
    {
        switch (type)
        {
        case Aircraft::Type::Eagle:
            return textures.get(Textures::ID::Eagle);

        case Aircraft::Type::Raptor:
            return textures.get(Textures::ID::Raptor);
        }

        // on retourne eagle par default pour éviter une erreur
        return textures.get(Textures::ID::Eagle);
    }
}

Aircraft::Aircraft(Type type, const TextureHolder& textures)
    : mType(type)
    , mSprite(toTexture(type, textures))
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
