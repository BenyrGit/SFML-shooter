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
 16-06-2026     Benjamin Paquette       Ajout d'un template pour exécuter les commandes
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

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function function)
{
    return [=](SceneNode& node, sf::Time deltaTime)
        {
            assert(dynamic_cast<GameObject*>(&node) != nullptr);

            function(static_cast<GameObject&>(node), deltaTime);
        };
}