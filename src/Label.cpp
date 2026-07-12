#include "Label.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{
    Label::Label(const std::string& text, const sf::Font& font, unsigned int characterSize)
        : mText(font, toSfString(text), characterSize)
    {
        mText.setFillColor(sf::Color::White);
        centerOrigin(mText);
    }

    void Label::setText(const std::string& text)
    {
        mText.setString(toSfString(text));
        centerOrigin(mText);
    }

    bool Label::isSelectable() const
    {
        return false;
    }

    void Label::handleEvent(const sf::Event&)
    {
        // Un label n’est pas interactif.
    }

    void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        target.draw(mText, states);
    }
}