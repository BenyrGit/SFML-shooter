#include "Entity.hpp"

Entity::Entity(int hitpoints)
    :mVelocity(0.f, 0.f)
    , mHitpoints(hitpoints)
{
}

void Entity::setVelocity(sf::Vector2f velocity)
{
    mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
    mVelocity.x = vx;
    mVelocity.y = vy;
}

void Entity::accelerate(sf::Vector2f velocity)
{
    mVelocity += velocity;
}

void Entity::accelerate(float vx, float vy)
{
    mVelocity.x += vx;
    mVelocity.y += vy;
}

sf::Vector2f Entity::getVelocity() const
{
    return mVelocity;
}

void Entity::damage(int points)
{
    mHitpoints -= points;
}

void Entity::repair(int points)
{
    mHitpoints += points;
}

void Entity::destroy()
{
    mHitpoints = 0;
}

int Entity::getHitpoints() const
{
    return mHitpoints;
}

bool Entity::isDestroyed() const
{
    return mHitpoints <= 0;
}

void Entity::updateCurrent(sf::Time deltaTime)
{
    move(mVelocity * deltaTime.asSeconds());
}