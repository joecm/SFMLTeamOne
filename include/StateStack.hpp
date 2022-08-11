#ifndef __STATESTACK_HPP__
#define __STATESTACK_HPP__

#include "../include/State.hpp"
#include "../include/ResourceHolder.hpp"
#include "../include/StateIdentifiers.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>

#include <utility>
#include <functional>
#include <map>

namespace sf
{
	class Event;
	class RenderWindow;
}

class StateStack : private sf::NonCopyable {
public:
    enum class Action { 
        Push,
        Pop,
        Clear
    };
public:
	explicit StateStack (State::Context context);
	~StateStack();
	// Función Miembro que emplea la factoria de funciones para agrupar el ID y el estado en el mapa de que es la factoría
	template <typename T>
	void registerState(ID stateID);

	void update(sf::Time dt);
	void draw();
	void handleEvent (const sf::Event& event);

	void pushState(ID stateID);
	void popState();
	void clearStates();

	bool isEmpty() const;

private:
    State::Ptr createState (ID stateID);
    void applyPendingChanges();

    struct PendingChange
    {
        explicit PendingChange(Action action, ID stateID = ID::None);
        /* data */
        Action action;
        ID stateID;
    };
private:
    std::vector<State::Ptr> mStack;
    std::vector<PendingChange> mPendingList;

    State::Context mContext;
    // creación de estados
    std::map<ID, std::function<State::Ptr()>> mFactories;
};

// Las templates hay que declararlas aquí o meter un include como hace en
// ResourceHolder.inl pero en el caso de que metas un .inl pierdes todos los
// colores del IDE.
template <typename T>
void StateStack::registerState(ID stateID)
{
	mFactories[stateID] = [this] () {
		return State::Ptr(new T(*this, mContext));
	};

	// por un momento la lambda me ha confundido, este retorno es el estado asociado al ID en el mapa
	// (en un elemento concreto) que es mFactories
	// me chocaba que la función (StateStack) retornara un shared ptr cuando el retorno es void
	// en realidad la función no devuelve nada, como digo asigna
}

#endif // __STATESTACK_HPP__