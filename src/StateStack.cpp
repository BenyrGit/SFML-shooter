#include "StateStack.hpp"

#include <cassert>

StateStack::StateStack(State::Context context)
    : mContext(context)
{}

void StateStack::update(sf::Time deltaTime)
{
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if (!(*itr)->update(deltaTime))
        {
            break;
        }
    }

    applyPendingChanges();
}

void StateStack::draw()
{
    for (State::Ptr& state : mStack)
    {
        state->draw();
    }
}

void StateStack::handleEvent(const sf::Event& event)
{
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if (!(*itr)->handleEvent(event))
        {
            break;
        }
    }

    applyPendingChanges();
}

void StateStack::pushState(States::ID stateID)
{
    mPendingList.emplace_back(Action::Push, stateID);
}

void StateStack::popState()
{
    mPendingList.emplace_back(Action::Pop);
}

void StateStack::clearStates()
{
    mPendingList.emplace_back(Action::Clear);
}

bool StateStack::isEmpty() const
{
    return mStack.empty();
}

State::Ptr StateStack::createState(States::ID stateID)
{
    const auto found = mFactories.find(stateID);

    assert(found != mFactories.end());

    return found->second();
}

void StateStack::applyPendingChanges()
{
    for (const PendingChange& change : mPendingList)
    {
        switch (change.action)
        {
        case Action::Push:
            mStack.push_back(createState(change.stateID));
            break;

        case Action::Pop:
            if (!mStack.empty())
            {
                mStack.pop_back();
            }
            break;

        case Action::Clear:
            mStack.clear();
            break;
        }
    }

    mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
    : action(action)
    , stateID(stateID)
{}