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

 ****************************************/
#pragma once

#include "State.hpp"

#include <SFML/Graphics/Text.hpp>

#include <vector>

class MenuState : public State
{
public:
    MenuState(StateStack& stack, Context context);

    void draw() override;
    bool update(sf::Time deltaTime) override;
    bool handleEvent(const sf::Event& event) override;

private:
    void updateOptionText();

private:
    std::vector<sf::Text> mOptions;
    std::size_t mOptionIndex = 0;
};