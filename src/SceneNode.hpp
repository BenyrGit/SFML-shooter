/****************************************
 Fichier		:	SceneNode.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Arbre qui regroupe les objets du jeu
 Date			:	12-06-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================
 12-06-2026     Benjamin Paquette       Ajout de méthodes pour déssiner un parent avant les enfants
 12-06-2026     Benjamin Paquette       Méthodes pour mettre à jour les objets
 ****************************************/
#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

class SceneNode : public sf::Transformable, public sf::Drawable
{
public:
    // Allias
    using Ptr = std::unique_ptr<SceneNode>;

    // Méthodes
    virtual ~SceneNode() = default;
    void attachChild(Ptr child);
    Ptr detachChild(const SceneNode& node);
    void update(sf::Time deltaTime);

private:
    // Méthodes
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time deltaTime);
    void updateChildren(sf::Time deltaTime);

    // Attributs
    std::vector<Ptr>    mChildren;
    SceneNode*          mParent = nullptr;
};