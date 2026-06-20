/****************************************
 Fichier		:	GameState.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Écran principale du jeu
 Date			:	19-06-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================

 ****************************************/
#pragma once

#include "State.hpp"
#include "World.hpp"

class GameState : public State
{
public:
    GameState(StateStack& stack, Context context);

    void draw() override;
    bool update(sf::Time deltaTime) override;
    bool handleEvent(const sf::Event& event) override;

private:
    World mWorld;
    Player* mPlayer = nullptr;
};