#ifndef __STATE_HPP__
#define __STATE_HPP__

#include "../include/ResourceHolder.hpp"
#include "../include/StateIdentifiers.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

namespace sf {
    class RenderWindow;
}

class StateStack;
class Player;

class State {
public:
    using Ptr = std::shared_ptr<State>;
    struct Context
    {
        Context(sf::RenderWindow& window, TextureHolder& textures,FontHolder& fonts, Player& player);
			sf::RenderWindow* window;
			TextureHolder* textures;
			FontHolder* fonts;
			Player* player; // es un manejador de eventos
    };
    
public: 
    State(StateStack& stack, Context context);
	virtual ~State();

	virtual void draw() = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;

protected:
	void requestStackPush(ID stateID);
	void requestStackPop();
	void requestStateClear();

	Context getContext() const;

private:
	StateStack* mStack;
	Context mContext;
};

#endif // __STATE_HPP__