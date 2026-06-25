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
 25-06-2026     Benjamin                Utilisation du GUI dans la pause
 ****************************************/
#pragma once

#include "Container.hpp"
#include "State.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

class PauseState : public State
{
public:
    PauseState(StateStack& stack, Context context);

    void draw() override;
    bool update(sf::Time deltaTime) override;
    bool handleEvent(const sf::Event& event) override;

private:
    sf::RectangleShape mBackgroundShape;
    GUI::Container mGuiContainer;
};