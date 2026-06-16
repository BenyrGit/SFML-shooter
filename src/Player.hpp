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
        MoveDown
    };

public:
    Player();

    void handleEvent(const sf::Event& event, CommandQueue& commands);
    void handleRealtimeInput(CommandQueue& commands);

private:
    void initializeActions();

private:
    std::map<sf::Keyboard::Key, Action> mKeyBinding;
    std::map<Action, Command> mActionBinding;
};