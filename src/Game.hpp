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
 15-06-2026     Benjamin                
 19-06-2026     Benjamin                Ajout des états
 20-06-2026     Benjamin                Ajout de la police
 20-06-2026     Benjamin                Chargement du titre au lieu du gameplay
 ****************************************/
#pragma once

#include "Player.hpp"
#include "ResourceTypes.hpp"
#include "StateStack.hpp"

#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();

    void run();

private:
    // Méthodes
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void registerStates();

    // Attributs
    sf::RenderWindow    mWindow;
    FontHolder mFonts;
    TextureHolder mTextures;
    Player mPlayer;
    StateStack mStateStack;
};