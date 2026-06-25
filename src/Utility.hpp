/****************************************
 Fichier		:	Utility.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Regroupe les fonctions utilitaires du programme
 Date			:	21-06-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================
 25-06-2026		Benjamin				Ajout fonction pour afficher les touches
 ****************************************/
#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

std::string toString(sf::Keyboard::Key key);