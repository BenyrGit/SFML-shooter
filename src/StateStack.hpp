/****************************************
 Fichier		:	StateStack.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Déclare la pile d'états et les opérations possibles : ajouter, retirer, vider et mettre à jour les états.
 Date			:	19-06-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================

 ****************************************/

#pragma once

#include "State.hpp"
#include "StateIdentifiers.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <functional>
#include <map>
#include <vector>

class StateStack
{
public:
    enum class Action
    {
        Push,
        Pop,
        Clear
    };

public:
    explicit StateStack(State::Context context);

    template <typename T>
    void registerState(States::ID stateID);

    void update(sf::Time deltaTime);
    void draw();
    void handleEvent(const sf::Event& event);

    void pushState(States::ID stateID);
    void popState();
    void clearStates();

    bool isEmpty() const;

private:
    State::Ptr createState(States::ID stateID);
    void applyPendingChanges();

private:
    struct PendingChange
    {
        explicit PendingChange(Action action, States::ID stateID = States::ID::None);

        Action action;
        States::ID stateID;
    };

private:
    std::vector<State::Ptr> mStack;
    std::vector<PendingChange> mPendingList;

    State::Context mContext;
    std::map<States::ID, std::function<State::Ptr()>> mFactories;
};

template <typename T>
void StateStack::registerState(States::ID stateID)
{
    mFactories[stateID] =
        [this]()
        {
            return std::make_unique<T>(*this, mContext);
        };
}