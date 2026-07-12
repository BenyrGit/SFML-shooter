#include "Button.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{
    Button::Button(const sf::Font& font)
        : mCallback()
        , mShape({ 300.f, 55.f })
        , mText(font, "", 28)
    {
        mShape.setOrigin({
            mShape.getSize().x / 2.f,
            mShape.getSize().y / 2.f
            });

        mShape.setFillColor(sf::Color(60, 60, 60));
        mShape.setOutlineThickness(2.f);
        mShape.setOutlineColor(sf::Color::White);

        mText.setFillColor(sf::Color::White);

        updateAppearance();
    }

    // Le callback est la fonction appelée quand le bouton est activé
    void Button::setCallback(Callback callback)
    {
        mCallback = std::move(callback);
    }

    void Button::setText(const std::string& text)
    {
        mText.setString(toSfString(text));
        centerOrigin(mText);
        mText.setPosition({ 0.f, -4.f });
    }

    bool Button::isSelectable() const
    {
        return true;
    }

    void Button::select()
    {
        Component::select();

        updateAppearance();
    }

    void Button::deselect()
    {
        Component::deselect();

        updateAppearance();
    }

    // le bouton devient actif. Il appelle son callback et se désactive
    void Button::activate()
    {
        Component::activate();

        if (mCallback)
        {
            mCallback();
        }

        deactivate();
    }

    void Button::deactivate()
    {
        Component::deactivate();

        updateAppearance();
    }

    void Button::handleEvent(const sf::Event&)
    {
        // le bouton est activé par le Container.
        // Donc pas besoin de gérer directement les événements.
    }

    // Change l'apparence selon l'état du bouton
    void Button::updateAppearance()
    {
        if (isSelected())
        {
            mShape.setFillColor(sf::Color(100, 100, 100));
            mShape.setOutlineColor(sf::Color::Yellow);
            mText.setFillColor(sf::Color::Yellow);
        }
        else
        {
            mShape.setFillColor(sf::Color(60, 60, 60));
            mShape.setOutlineColor(sf::Color::White);
            mText.setFillColor(sf::Color::White);
        }
    }

    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        target.draw(mShape, states);
        target.draw(mText, states);
    }
}