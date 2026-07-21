/****************************************
 Fichier		:	Player.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Gestion du joueur
 Date			:	15-06-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================
 16-06-2026     Benjamin Paquette       Ajout d'actions
 16-06-2026     Benjamin Paquette       Méthodes pour configurer les touches
 28-06-2026     Benjamin Paquette       Méthode pour reset les touches au valeur par défaut
 20-07-2026     Benjamin Paquette       La vitesse vient de la classe Aircraft et non plus en dur dans Player
 ****************************************/
#pragma once

#include "Command.hpp"
#include "CommandQueue.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <map>

class Player
{
public:
    enum class Action
    {
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown,
        Fire,
        LaunchMissile
    };

public:
    Player();

    void handleEvent(const sf::Event& event, CommandQueue& commands);
    void handleRealtimeInput(CommandQueue& commands);

    void assignKey(Action action, sf::Keyboard::Key key);
    sf::Keyboard::Key getAssignedKey(Action action) const;

    void resetKeyBindings();
private:
    // Méthodes
    void initializeActions();
    void initializeKeyBindings();
    static bool isRealtimeAction(Action action);

    // Attributs
    std::map<sf::Keyboard::Key, Action> mKeyBinding;
    std::map<Action, Command> mActionBinding;
};