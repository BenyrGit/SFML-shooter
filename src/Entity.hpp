/****************************************
 Fichier		:	Entity.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	SceneNode qui gère les entité avec une vitesse
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

class Entity : public SceneNode
{
public:
    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float vx, float vy);

    sf::Vector2f getVelocity() const;

private:
    void updateCurrent(sf::Time deltaTime) override;

    sf::Vector2f mVelocity{ 0.f, 0.f };
};