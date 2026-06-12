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

 ****************************************/
#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

class SceneNode : public sf::Transformable, public sf::Drawable
{
public:
    using Ptr = std::unique_ptr<SceneNode>;

public:
    void attachChild(Ptr child);
    Ptr detachChild(const SceneNode& node);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    std::vector<Ptr> mChildren;
    SceneNode* mParent = nullptr;
};