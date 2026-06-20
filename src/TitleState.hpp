/****************************************
 Fichier		:	TitleState.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Écran titre
 Date			:	20-06-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================
 20-06-2026     Benjamin Paquette       Changement du prochain écran : game > menu
 ****************************************/
#pragma once

#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class TitleState : public State
{
public:
    TitleState(StateStack& stack, Context context);

    void draw() override;
    bool update(sf::Time deltaTime) override;
    bool handleEvent(const sf::Event& event) override;

private:
    sf::Text mTitleText;
    sf::Text mInstructionText;

    sf::Time mTextEffectTime = sf::Time::Zero;
    bool mShowInstruction = true;
};