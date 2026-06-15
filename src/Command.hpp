/****************************************
 Fichier		:	Command.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Crée les actions à exécuter
 Date			:	15-06-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================

 ****************************************/
#pragma once

#include "Category.hpp"

#include <SFML/System/Time.hpp>

#include <functional>

// déclaration anticipée
class SceneNode;

struct Command
{
    std::function<void(SceneNode&, sf::Time)> action;
    unsigned int category = Category::None;
};