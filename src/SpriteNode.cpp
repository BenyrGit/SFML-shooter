#include "SpriteNode.hpp"

namespace
{
    // fonction interne pour centrer le sprite
    void centerOrigin(sf::Sprite& sprite)
    {
        const sf::FloatRect bounds = sprite.getLocalBounds();

        sprite.setOrigin({
            bounds.position.x + bounds.size.x / 2.f,
            bounds.position.y + bounds.size.y / 2.f
            });
    }
}

SpriteNode::SpriteNode(const sf::Texture& texture)
    : mSprite(texture)
{
    centerOrigin(mSprite);
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}


sf::FloatRect SpriteNode::getBoundingRect() const
{
    // on utiliser getWorldTransform pour avoir toutes les transformations incluant les parents 
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}