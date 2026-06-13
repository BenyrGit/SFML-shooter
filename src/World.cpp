#include "World.hpp"

World::World(sf::RenderWindow& window)
    : mWindow(window)
    , mTextures()
    , mSceneGraph()
    , mPlayerAircraft(nullptr)
{
    loadTextures();
    buildScene();
}

void World::loadTextures()
{
    mTextures.load(Textures::ID::Eagle, "assets/textures/Eagle.png");
    mTextures.load(Textures::ID::Raptor, "assets/textures/Raptor.png");
    // mTextures.load(Textures::ID::Desert, "assets/textures/Desert.png");
}

// Construit les différentes couches du monde
void World::buildScene()
{
    auto player = std::make_unique<Aircraft>(Aircraft::Type::Eagle, mTextures);
    player->setPosition({ 512.f, 384.f });

    mPlayerAircraft = player.get();

    mSceneGraph.attachChild(std::move(player));
}

void World::update(sf::Time deltaTime)
{
    mSceneGraph.update(deltaTime);

    keepPlayerInsideWindow();
}

void World::draw()
{
    mWindow.draw(mSceneGraph);
}

void World::handlePlayerMovement(sf::Vector2f movement, sf::Time deltaTime)
{
    mPlayerAircraft->move(movement * deltaTime.asSeconds());
}

void World::keepPlayerInsideWindow()
{
    sf::Vector2f position = mPlayerAircraft->getPosition();
    const sf::FloatRect bounds = mPlayerAircraft->getBoundingRect();

    const float halfWidth = bounds.size.x / 2.f;
    const float halfHeight = bounds.size.y / 2.f;

    const sf::Vector2u windowSize = mWindow.getSize();

    if (position.x < halfWidth)
    {
        position.x = halfWidth;
    }
    else if (position.x > static_cast<float>(windowSize.x) - halfWidth)
    {
        position.x = static_cast<float>(windowSize.x) - halfWidth;
    }

    if (position.y < halfHeight)
    {
        position.y = halfHeight;
    }
    else if (position.y > static_cast<float>(windowSize.y) - halfHeight)
    {
        position.y = static_cast<float>(windowSize.y) - halfHeight;
    }

    mPlayerAircraft->setPosition(position);
}