#include "SceneNode.hpp"

#include <algorithm>
#include <cassert>

void SceneNode::attachChild(Ptr child)
{
    child->mParent = this;

    mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
    const auto found = std::find_if(
        mChildren.begin(),
        mChildren.end(),
        [&](Ptr& p)
        {
            return p.get() == &node;
        });

    assert(found != mChildren.end());

    Ptr result = std::move(*found);

    result->mParent = nullptr;

    mChildren.erase(found);

    return result;
}

void SceneNode::update(sf::Time deltaTime)
{
    updateCurrent(deltaTime);
    updateChildren(deltaTime);
}

sf::Transform SceneNode::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;

    // On part de this et on remonte tous les parents pour avoir toutes les transformations
    for (const SceneNode* node = this; node != nullptr; node = node->mParent)
    {
        // on combine les transformations
        transform = node->getTransform() * transform;
    }

    return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
    return getWorldTransform().transformPoint({ 0.f, 0.f });
}

unsigned int SceneNode::getCategory() const
{
    return Category::Scene;
}


void SceneNode::onCommand(const Command& command, sf::Time deltaTime)
{
    // on vérifie si la commande est pour le noeud courant
    if (command.category & getCategory())
    {
        command.action(*this, deltaTime);
    }

    // Récursive sur les enfants
    for (Ptr& child : mChildren)
    {
        child->onCommand(command, deltaTime);
    }
}

void SceneNode::draw(
    sf::RenderTarget& target,
    sf::RenderStates states
) const
{
    // permet d'ajouter les transformations du parent aux l'enfants
    states.transform *= getTransform();

    drawCurrent(target, states);
    drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    // méthode virtuelle
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const Ptr& child : mChildren)
    {
        target.draw(*child, states);
    }
}

void SceneNode::updateCurrent(sf::Time deltaTime)
{
}

void SceneNode::updateChildren(sf::Time deltaTime)
{
    for (Ptr& child : mChildren)
    {
        child->update(deltaTime);
    }
}
