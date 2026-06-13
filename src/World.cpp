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
    // On crée toutes les couches du monde
    for (std::size_t i = 0; i < mSceneLayers.size(); ++i)
    {
        // chaque couche est un SceneNode
        auto layer = std::make_unique<SceneNode>();

        mSceneLayers[i] = layer.get();

        // Le SceneGraph est le propriétaire des couches
        mSceneGraph.attachChild(std::move(layer));
    }

    auto player = std::make_unique<Aircraft>(Aircraft::Type::Eagle, mTextures);
    player->setPosition({ 512.f, 384.f });

    mPlayerAircraft = player.get();

    // Le joueur est attaché à la couche Air
    mSceneLayers[toIndex(Layer::Air)]->attachChild(std::move(player));
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

std::size_t World::toIndex(World::Layer layer)
{
    return static_cast<std::size_t>(layer);
}
