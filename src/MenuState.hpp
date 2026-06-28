/****************************************
 Fichier		:	MenuState.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Écran du menu
 Date			:	20-06-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================
 24-06-20226    Benjamin                Ajout de composant : label et boutons
 28-06-20226    Benjamin                Ajout du bouton options
 ****************************************/
#pragma once

#include "Container.hpp"
#include "State.hpp"

class MenuState : public State
{
public:
    MenuState(StateStack& stack, Context context);

    void draw() override;
    bool update(sf::Time deltaTime) override;
    bool handleEvent(const sf::Event& event) override;

private:
    GUI::Container mGUIContainer;
};