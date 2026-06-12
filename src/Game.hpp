/****************************************
 Fichier		:	Game.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Gestion de la logique du jeu
 Date			:	08-06-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================
 12-06-2026     Benjamin                ajout de sceneNode
 ****************************************/
#pragma once

#include "ResourceTypes.hpp"
#include "SceneNode.hpp"

#include <SFML/Graphics.hpp>
#include <optional>


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
    void keepPlayerInsideWindow();

    // Attributs
    sf::RenderWindow            mWindow;
    TextureHolder               mTextures;
    std::optional<sf::Sprite>   mPlayerSprite;  // On utilise optional pour ne pas avoir à construire le sprite avant de charger la texture  
    SceneNode                   mSceneGraph;

    bool mIsMovingUp    = false;
    bool mIsMovingDown  = false;
    bool mIsMovingLeft  = false;
    bool mIsMovingRight = false;
};