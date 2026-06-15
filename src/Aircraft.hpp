/****************************************
 Fichier		:	Aircraft.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Classe qui gère les objets avion
 Date			:	13-06-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================
 
 ****************************************/
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
    unsigned int getCategory() const override;

private:
    // Méthodes
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Attributs
    Type mType;
    sf::Sprite mSprite;
};