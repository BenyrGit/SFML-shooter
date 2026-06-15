/****************************************
 Fichier		:	CommandQueue.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Stoke les commandes avant de les exécuter
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

#include <queue>

class CommandQueue
{
public:
    void push(const Command& command);
    Command pop();

    bool isEmpty() const;

private:
    std::queue<Command> mQueue;
};