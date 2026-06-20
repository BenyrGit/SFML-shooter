/****************************************
 Fichier		:	ResourceHolder.hpp
 Auteur			:	Benjamin Paquette
 Fonctionnalité :	Template - Gestionnaire de ressource
 Date			:	09-06-2026

 Vérification	:
 JJ-MM-AAAA     Nom                     Approuvé
 =========================================================

 Historique de modifications :
 JJ-MM-AAAA     Nom                     Commentaire
 =========================================================
 11-09-2026     Benjamin                Surcharge de load
 20-06-2026     Benjamin                Ajout de la gestion de font SFML 3.0 : loadResourceFromFile
 ****************************************/
#pragma once

#include <cassert>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

namespace Detail
{
    template <typename>
    inline constexpr bool AlwaysFalse = false;

    template <typename Resource, typename... Args>
    bool loadResourceFromFile(Resource& resource, const std::string& filename, Args&&... args)
    {
        // Vérifie si la ressource possède loadFromFile : Texture
        if constexpr (requires { resource.loadFromFile(filename, std::forward<Args>(args)...); })
        {
            return resource.loadFromFile(filename, std::forward<Args>(args)...);
        }
        // Vérifie si la ressource possède openFromFile : Fonts
        else if constexpr (requires { resource.openFromFile(filename, std::forward<Args>(args)...); })
        {
            return resource.openFromFile(filename, std::forward<Args>(args)...);
        }
        else
        {
            static_assert(
                AlwaysFalse<Resource>,
                "Cette ressource ne possède ni loadFromFile(), ni openFromFile()."
                );
        }
    }
}

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
    void load(Identifier id, const std::string& filename);

    template <typename... Args>
    void load(Identifier id, const std::string& filename, Args&&... args);

    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;

private:
    void insertResource(Identifier id, std::unique_ptr<Resource> resource);

    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
    auto resource = std::make_unique<Resource>();

    if (!Detail::loadResourceFromFile(*resource, filename))
    {
        throw std::runtime_error("ResourceHolder::load - Impossible de charger " + filename);
    }

    insertResource(id, std::move(resource));
}

// Surcharge de load pour accepter tous les paramètres supplémentaire.
template <typename Resource, typename Identifier>
template <typename... Args>
void ResourceHolder<Resource, Identifier>::load(
    Identifier id,
    const std::string& filename,
    Args&&... args
)
{
    auto resource = std::make_unique<Resource>();

    if (!Detail::loadResourceFromFile(*resource, filename, std::forward<Args>(args)...))
    {
        throw std::runtime_error("ResourceHolder::load - Impossible de charger " + filename);
    }

    insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
    const auto found = mResourceMap.find(id);

    assert(found != mResourceMap.end());

    return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
    const auto found = mResourceMap.find(id);

    assert(found != mResourceMap.end());

    return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource)
{
    const auto [iterator, inserted] = mResourceMap.insert({ id, std::move(resource) });

    assert(inserted);
}

