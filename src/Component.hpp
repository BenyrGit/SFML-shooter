/****************************************
 Fichier		:	Component.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Base pour les éléments GUI
 Date			:	23-06-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================

 ****************************************/
#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

namespace GUI
{
    class Component : public sf::Drawable, public sf::Transformable
    {
    public:
        using Ptr = std::unique_ptr<Component>;

    public:
        Component() = default;
        ~Component() override = default;

        // On désactive les copies 
        Component(const Component&) = delete;
        Component& operator=(const Component&) = delete;

        virtual bool isSelectable() const = 0;  // Permet de savoir si un élément peut être sélectionné

        bool isSelected() const;
        virtual void select();
        virtual void deselect();

        bool isActive() const;
        virtual void activate();
        virtual void deactivate();

        virtual void handleEvent(const sf::Event& event) = 0;

    private:
        bool mIsSelected = false;
        bool mIsActive = false;
    };
}