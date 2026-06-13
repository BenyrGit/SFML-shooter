/****************************************
 Fichier		:	Game.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Relie les différents éléments du jeu
 Date			:	08-06-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================
 12-06-2026     Benjamin                ajout de sceneNode
 13-06-2026     Benjamin                Transfert de la logique vers World
 ****************************************/
#pragma once

#include "World.hpp"

#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();

    void run();

private:
    // Méthodes
    void processEvents();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    void update(sf::Time deltaTime);
    void render();

    // Attributs
    sf::RenderWindow    mWindow;
    World mWorld;

    bool mIsMovingUp    = false;
    bool mIsMovingDown  = false;
    bool mIsMovingLeft  = false;
    bool mIsMovingRight = false;
};