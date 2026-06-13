/****************************************
 Fichier		:	World.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Gestion de la logique du jeu
 Date			:	13-06-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================
           
 ****************************************/
#pragma once

#include "Aircraft.hpp"
#include "ResourceTypes.hpp"
#include "SceneNode.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <array>

class World
{
public:
    // World reçoit la fenêtre pour pouvoir dessiner dedans
    explicit World(sf::RenderWindow& window);

    void update(sf::Time deltaTime);
    void draw();

    void handlePlayerMovement(sf::Vector2f movement, sf::Time deltaTime);

private:

    enum class Layer
    {
        Background,
        Air,
        LayerCount
    };

    void loadTextures();
    void buildScene();
    void keepPlayerInsideWindow();

    static std::size_t toIndex(Layer layer);

private:
    sf::RenderWindow& mWindow;

    TextureHolder mTextures;
    SceneNode mSceneGraph;

    std::array<SceneNode*, static_cast<std::size_t>(Layer::LayerCount)> mSceneLayers{};

    Aircraft* mPlayerAircraft = nullptr;
};