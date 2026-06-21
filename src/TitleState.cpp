#include "TitleState.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

TitleState::TitleState(StateStack& stack, Context context)
    : State(stack, context)
    , mTitleText(context.fonts->get(Fonts::ID::Main), "SFML Shooter", 60)
    , mInstructionText(context.fonts->get(Fonts::ID::Main), "Appuie sur une touche pour commencer", 28)
{
    const sf::Vector2f viewSize = context.window->getView().getSize();

    centerOrigin(mTitleText);
    mTitleText.setPosition({
        viewSize.x / 2.f,
        viewSize.y / 2.f - 80.f
        });

    centerOrigin(mInstructionText);
    mInstructionText.setPosition({
        viewSize.x / 2.f,
        viewSize.y / 2.f + 80.f
        });
}

void TitleState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    window.draw(mTitleText);

    if (mShowInstruction)
    {
        window.draw(mInstructionText);
    }
}

bool TitleState::update(sf::Time deltaTime)
{
    mTextEffectTime += deltaTime;

    if (mTextEffectTime >= sf::seconds(0.5f))
    {
        mShowInstruction = !mShowInstruction;
        mTextEffectTime = sf::Time::Zero;
    }

    return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
    if (event.is<sf::Event::KeyPressed>())
    {
        requestStackPop();
        requestStackPush(States::ID::Menu);
    }

    return true;
}