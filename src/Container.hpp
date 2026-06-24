/****************************************
 Fichier		:	Container.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Composant GUI capable de contenur d'autres composants
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

#include <vector>

namespace GUI
{
    class Container : public Component
    {
    public:
        Container();

        void pack(Component::Ptr component);

        bool isSelectable() const override;
        void handleEvent(const sf::Event& event) override;

    private:
        bool hasSelection() const;
        void select(std::size_t index);
        void selectNext();
        void selectPrevious();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        std::vector<Component::Ptr> mChildren;

        std::size_t mSelectedChild = 0;
        bool mHasSelection = false;
    };
}