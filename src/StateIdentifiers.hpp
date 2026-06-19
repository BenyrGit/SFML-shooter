/****************************************
 Fichier		:	StateIdentifiers.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Definie les états possible du jeu
 Date			:	18-06-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================
 
 ****************************************/
#pragma once

namespace States
{
    enum class ID
    {
        None,
        Title,
        Menu,
        Game,
        Pause,
        Loading
    };
}