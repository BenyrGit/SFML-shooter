/****************************************
 Fichier		:	SpriteNode.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Enfant de SceneNode, gère un type de Scene particulier : joueur, ennemis, background...
 Date			:	12-06-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================

 ****************************************/
#pragma once

#include "SceneNode.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class SpriteNode : public SceneNode
{
public:
    explicit SpriteNode(const sf::Texture& texture);

private:
    // Méthode
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Attribut
    sf::Sprite mSprite;
};