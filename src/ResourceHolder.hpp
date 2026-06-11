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

 ****************************************/
#pragma once

#include <cassert>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
    void load(Identifier id, const std::string& filename);

    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;

private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
    auto resource = std::make_unique<Resource>();

    if (!resource->loadFromFile(filename))
    {
        throw std::runtime_error("ResourceHolder::load - Impossible de charger " + filename);
    }

    const auto [iterator, inserted] = mResourceMap.insert({ id, std::move(resource) });

    assert(inserted);
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