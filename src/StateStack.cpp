#include "../include/StateStack.hpp"
#include <cassert>
StateStack::StateStack(State::Context context) :
mStack(), mPendingList(), mContext(context), mFactories()
{

}

StateStack::~StateStack() {
}


State::Ptr StateStack::createState(ID stateID)
{
    // Busca un objeto creado ya
    auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

	return found->second();
}

void StateStack::applyPendingChanges()
{
	for (PendingChange change : mPendingList) 
    {
		switch (change.action) 
        {
			case Action::Push :
				mStack.push_back(createState(change.stateID));
				break;
			case Action::Pop :
				mStack.pop_back();
				break;
			case Action::Clear :
				mStack.clear();
				break;
		}
	}
	mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, ID stateID)
: action(action) , stateID(stateID)
{
}

void StateStack::update(sf::Time dt)
{
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) 
    {
		if (!(*itr)->update(dt))
			break;
    }
    applyPendingChanges();
}

void StateStack::draw()
{
// recorre todos los estados y los dibuja, para que sean transparentes
// pueden aparecer cosas de otros estados, veremos como ocultarlas con
// RectangleShapes de un color
    for (State::Ptr& state : mStack) 
    {
        state->draw();
    }
    
}

void StateStack::handleEvent(const sf::Event& event)
{
    // Iterate from top to bottom and stop if handleEvent return false
	// como es un vector usa un reverse iterator.
	// si algún estado retorna falso sale, es la manera de que un estado impida
	// que el evento fluya a otro estado, ver los hadleEvent en los states
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) 
    {
		if (!(*itr)->handleEvent(event))
			break;
	}
	applyPendingChanges();      
}

void StateStack::pushState(ID stateID) {
	mPendingList.push_back(PendingChange(Action::Push, stateID));
}

void StateStack::popState() {
	mPendingList.push_back(PendingChange(Action::Pop));
}

void StateStack::clearStates() {
	mPendingList.push_back(PendingChange(Action::Clear));
}

bool StateStack::isEmpty() const {
	return mStack.empty();
}


