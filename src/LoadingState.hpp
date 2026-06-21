/****************************************
 Fichier		:	LoadingState.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Écran de chargement
 Date			:	21-06-2026

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

class LoadingState : public State
{
public:
    LoadingState(StateStack& stack, Context context);

    void draw() override;
    bool update(sf::Time deltaTime) override;
    bool handleEvent(const sf::Event& event) override;

private:
    sf::Text mLoadingText;
    bool mGameStateCreated = false;
};