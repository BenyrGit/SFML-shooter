/****************************************
 Fichier		:	DataTbles.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Déclare les structures qui continnent les données des objets : avions, ennemies, projectiles...
 Date			:	18-07-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================

 ****************************************/
#pragma once

#include "ResourceIdentifiers.hpp"
#include "Aircraft.hpp"

#include <array>

struct AircraftData
{
	int hitpoints;
	float speed;
	Textures::ID texture;
};

std::array<AircraftData, static_cast<std::size_t>(Aircraft::Type::TypeCount)> initializeAircraftData();