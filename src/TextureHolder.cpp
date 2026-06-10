#include "TextureHolder.hpp"

#include <cassert>
#include <stdexcept>

void TextureHolder::load(Textures::ID id, const std::string& filename)
{
    // texture possédée par un unique_ptr
    auto texture = std::make_unique<sf::Texture>();

    if (!texture->loadFromFile(filename))
    {
        throw std::runtime_error("TextureHolder::load - Impossible de charger " + filename);
    }

    // Structured binding
    const auto [iterator, inserted] = mTextureMap.insert({ id, std::move(texture) });

    assert(inserted);
}

sf::Texture& TextureHolder::get(Textures::ID id)
{
    const auto found = mTextureMap.find(id);

    assert(found != mTextureMap.end());

    return *found->second;
}

const sf::Texture& TextureHolder::get(Textures::ID id) const
{
    const auto found = mTextureMap.find(id);

    assert(found != mTextureMap.end());

    return *found->second;
}