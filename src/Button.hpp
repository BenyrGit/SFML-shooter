/****************************************
 Fichier		:	Button.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Déclare un bouton GUI
 Date			:	23-06-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================

 ****************************************/
#pragma once

#include "Component.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <functional>
#include <string>

namespace GUI
{
    class Button : public Component
    {
    public:
        using Callback = std::function<void()>;

    public:
        explicit Button(const sf::Font& font);

        void setCallback(Callback callback);
        void setText(const std::string& text);

        bool isSelectable() const override;

        void select() override;
        void deselect() override;

        void activate() override;
        void deactivate() override;

        void handleEvent(const sf::Event& event) override;

    private:
        void updateAppearance();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        Callback mCallback;

        sf::RectangleShape mShape;
        sf::Text mText;
    };
}