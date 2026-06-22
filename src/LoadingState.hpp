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
 22-06-2026     Benjamin Paquette       Ajout d'une barre de chargement
 ****************************************/
#pragma once

#include "State.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class LoadingState : public State
{
public:
    LoadingState(StateStack& stack, Context context);

    void draw() override;
    bool update(sf::Time deltaTime) override;
    bool handleEvent(const sf::Event& event) override;

private:
    // Méthodes
    void setProgress(float percent);

    // attributs
    sf::Text mLoadingText;

    sf::RectangleShape mProgressBarBackground;
    sf::RectangleShape mProgressBar;

    sf::Time mElapsedTime = sf::Time::Zero;
    sf::Time mLoadingDuration = sf::seconds(1.f);       // Temps de chargement simulée

    bool mGameStateCreated = false;                     // pour être évité de demandé plusieurs foit l'état Game
};