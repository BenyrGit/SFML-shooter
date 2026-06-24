#include "Container.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace GUI
{
    Container::Container()
        : mChildren()
        , mSelectedChild(0)
        , mHasSelection(false)
    {}

    // Ajoute un component dans le conteneur
    void Container::pack(Component::Ptr component)
    {
        mChildren.push_back(std::move(component));

        if (!hasSelection() && mChildren.back()->isSelectable())
        {
            select(mChildren.size() - 1);
        }
    }

    // Le conteneur n'est pas sélectionnable
    bool Container::isSelectable() const
    {
        return false;
    }

    // Gère le changement de d'option et l'activation de l'option sélectionné
    void Container::handleEvent(const sf::Event& event)
    {
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::W
                || keyPressed->code == sf::Keyboard::Key::Up)
            {
                selectPrevious();
            }
            else if (keyPressed->code == sf::Keyboard::Key::S
                || keyPressed->code == sf::Keyboard::Key::Down)
            {
                selectNext();
            }
            else if (keyPressed->code == sf::Keyboard::Key::Enter
                || keyPressed->code == sf::Keyboard::Key::Space)
            {
                if (hasSelection())
                {
                    mChildren[mSelectedChild]->activate();
                }
            }
        }

        if (hasSelection())
        {
            mChildren[mSelectedChild]->handleEvent(event);
        }
    }

    bool Container::hasSelection() const
    {
        return mHasSelection;
    }

    void Container::select(std::size_t index)
    {
        if (mChildren.empty())
        {
            return;
        }

        if (hasSelection())
        {
            mChildren[mSelectedChild]->deselect();
        }

        mSelectedChild = index;
        mChildren[mSelectedChild]->select();

        mHasSelection = true;
    }

    // Cherche le prochain élément sélectionnable
    void Container::selectNext()
    {
        if (mChildren.empty())
        {
            return;
        }

        if (!hasSelection())
        {
            select(0);
            return;
        }

        std::size_t next = mSelectedChild;

        do
        {
            next = (next + 1) % mChildren.size();
        } while (!mChildren[next]->isSelectable());

        select(next);
    }

    // Cherche le précédent élément sélectionnable
    void Container::selectPrevious()
    {
        if (mChildren.empty())
        {
            return;
        }

        if (!hasSelection())
        {
            select(0);
            return;
        }

        std::size_t previous = mSelectedChild;

        do
        {
            if (previous == 0)
            {
                previous = mChildren.size() - 1;
            }
            else
            {
                --previous;
            }
        } while (!mChildren[previous]->isSelectable());

        select(previous);
    }

    void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        for (const Component::Ptr& child : mChildren)
        {
            target.draw(*child, states);
        }
    }
}