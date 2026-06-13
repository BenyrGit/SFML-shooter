#pragma once

#include "Entity.hpp"
#include "ResourceTypes.hpp"

#include <SFML/Graphics/Sprite.hpp>

class Aircraft : public Entity
{
public:
    enum class Type
    {
        Eagle,
        Raptor
    };

    // Méthodes
    Aircraft(Type type, const TextureHolder& textures);

    sf::FloatRect getBoundingRect() const;

private:
    // Méthodes
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Attributs
    Type mType;
    sf::Sprite mSprite;
};