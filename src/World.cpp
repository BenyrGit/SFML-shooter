#include "World.hpp"
#include "SpriteNode.hpp"

namespace
{
    constexpr float ScrollSpeed = -50.f;

    constexpr float ViewWidth = 1024.f;
    constexpr float ViewHeight = 768.f;
    constexpr float WorldHeight = 3000.f;
}

World::World(sf::RenderWindow& window)
    : mWindow(window)
    , mWorldView(window.getDefaultView())
    , mTextures()
    , mSceneGraph()
    , mPlayerAircraft(nullptr)
{
    loadTextures();
    buildScene();

    mWorldView.setCenter({ ViewWidth / 2.f, WorldHeight - ViewHeight / 2.f });
}

void World::loadTextures()
{
    mTextures.load(Textures::ID::Eagle, "assets/textures/Eagle.png");
    mTextures.load(Textures::ID::Raptor, "assets/textures/Raptor.png");
    mTextures.load(Textures::ID::Desert, "assets/textures/Desert.png");
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

    // Background
    const sf::Texture& desertTexture = mTextures.get(Textures::ID::Desert);
    const sf::Vector2u textureSize = desertTexture.getSize();

    for (float y = 0.f; y < WorldHeight; y += static_cast<float>(textureSize.y))
    {
        auto background = std::make_unique<SpriteNode>(desertTexture);

        background->setPosition({
            ViewWidth / 2.f,
            y + static_cast<float>(textureSize.y) / 2.f
            });

        mSceneLayers[toIndex(Layer::Background)]->attachChild(std::move(background));
    }

    // Joueur
    auto player = std::make_unique<Aircraft>(Aircraft::Type::Eagle, mTextures);
    player->setPosition({ ViewWidth / 2.f, WorldHeight - ViewHeight / 4.f });

    mPlayerAircraft = player.get();

    // Le joueur est attaché à la couche Air
    mSceneLayers[toIndex(Layer::Air)]->attachChild(std::move(player));
}

void World::update(sf::Time deltaTime)
{
    // scrolling de la camera
    if (mWorldView.getCenter().y > ViewHeight / 2.f)
    {
        mWorldView.move({ 0.f, ScrollSpeed * deltaTime.asSeconds() });
    }

    mSceneGraph.update(deltaTime);

    keepPlayerInsideWindow();
}

void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

void World::setPlayerVelocity(sf::Vector2f velocity)
{
    velocity.y += ScrollSpeed;

    mPlayerAircraft->setVelocity(velocity);
}

void World::keepPlayerInsideWindow()
{
    sf::Vector2f position = mPlayerAircraft->getPosition();
    const sf::FloatRect bounds = mPlayerAircraft->getBoundingRect();

    const float halfWidth = bounds.size.x / 2.f;
    const float halfHeight = bounds.size.y / 2.f;

    const sf::Vector2f viewCenter = mWorldView.getCenter();
    const sf::Vector2f viewSize = mWorldView.getSize();

    const float left = viewCenter.x - viewSize.x / 2.f;
    const float right = viewCenter.x + viewSize.x / 2.f;
    const float top = viewCenter.y - viewSize.y / 2.f;
    const float bottom = viewCenter.y + viewSize.y / 2.f;

    if (position.x < left + halfWidth)
    {
        position.x = left + halfWidth;
    }
    else if (position.x > right - halfWidth)
    {
        position.x = right - halfWidth;
    }

    if (position.y < top + halfHeight)
    {
        position.y = top + halfHeight;
    }
    else if (position.y > bottom - halfHeight)
    {
        position.y = bottom - halfHeight;
    }

    mPlayerAircraft->setPosition(position);
}

std::size_t World::toIndex(World::Layer layer)
{
    return static_cast<std::size_t>(layer);
}
