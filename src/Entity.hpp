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
 15-06-2026     Benjamin Paquette       Ajout de la méthode accelerate
 20-07-2026     Benjamin Paquette       Ajout de points de vie + méthodes
 ****************************************/
#pragma once

#include "SceneNode.hpp"

class Entity : public SceneNode
{
public:
    explicit Entity(int hitpoints);

    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float vx, float vy);

    void accelerate(sf::Vector2f velocity);
    void accelerate(float vx, float vy);

    sf::Vector2f getVelocity() const;

    void damage(int points);
    void repair(int points);
    void destroy();

    int getHitpoints() const;
    bool isDestroyed() const;

private:
    // méthodes
    void updateCurrent(sf::Time deltaTime) override;

    // attributs
    sf::Vector2f mVelocity{ 0.f, 0.f };
    int mHitpoints = 0;
};