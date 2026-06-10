#pragma once

#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Texture.hpp>

#include <map>
#include <memory>
#include <string>

class TextureHolder
{
public:
    void load(Textures::ID id, const std::string& filename);

    sf::Texture& get(Textures::ID id);
    const sf::Texture& get(Textures::ID id) const;

private:
    // On associe un Id à une texture
    // unique_ptr pour qu'une seule texture soit créée 
    std::map<Textures::ID, std::unique_ptr<sf::Texture>> mTextureMap;
};