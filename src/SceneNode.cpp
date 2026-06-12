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

void SceneNode::draw(
    sf::RenderTarget& target,
    sf::RenderStates states
) const
{
    // permet d'ajouter les transformations du parent aux l'enfants
    states.transform *= getTransform();

    for (const Ptr& child : mChildren)
    {
        target.draw(*child, states);
    }
}