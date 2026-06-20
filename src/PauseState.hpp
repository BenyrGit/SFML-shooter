/****************************************
 Fichier		:	PauseState.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Écran de pause
 Date			:	20-06-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================
 
 ****************************************/
#pragma once

#include "State.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class PauseState : public State
{
public:
    PauseState(StateStack& stack, Context context);

    void draw() override;
    bool update(sf::Time deltaTime) override;
    bool handleEvent(const sf::Event& event) override;

private:
    sf::RectangleShape mBackgroundShape;
    sf::Text mPausedText;
    sf::Text mInstructionText;
};