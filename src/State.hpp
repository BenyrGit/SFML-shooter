/****************************************
 Fichier		:	State.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Définit l’interface commune de tous les écrans du jeu : titre, menu, jeu, pause, etc.
 Date			:	19-06-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================
 
 ****************************************/
#pragma once

#include "ResourceTypes.hpp"
#include "StateIdentifiers.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

namespace sf
{
    class RenderWindow;
}

class Player;
class StateStack;

class State
{
public:
    using Ptr = std::unique_ptr<State>;

    // permet de partager les objets importants sans variables globales
    struct Context
    {
        sf::RenderWindow* window = nullptr;
        TextureHolder* textures = nullptr;
        FontHolder* fonts = nullptr;
        Player* player = nullptr;
    };

public:
    explicit State(StateStack& stack, Context context);
    virtual ~State() = default;

    virtual void draw() = 0;
    virtual bool update(sf::Time deltaTime) = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;

protected:
    void requestStackPush(States::ID stateID);
    void requestStackPop();
    void requestStateClear();

    Context getContext() const;

private:
    StateStack* mStack = nullptr;
    Context mContext;
};