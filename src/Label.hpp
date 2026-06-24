/****************************************
 Fichier		:	Label.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Composant GUI qui affiche du texte
 Date			:	24-06-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================

 ****************************************/
#pragma once

#include "Component.hpp"

#include <SFML/Graphics/Text.hpp>

#include <string>

namespace GUI
{
    class Label : public Component
    {
    public:
        Label(const std::string& text, const sf::Font& font, unsigned int characterSize = 24);

        void setText(const std::string& text);

        bool isSelectable() const override;
        void handleEvent(const sf::Event& event) override;

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        sf::Text mText;
    };
}