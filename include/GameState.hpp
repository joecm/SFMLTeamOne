#ifndef __GAMESTATE_HPP__
#define __GAMESTATE_HPP__

#include "../include/State.hpp"
#include "../include/World.hpp"
#include "../include/Player.hpp"

class GameState : public State 
{
private:
    World mWorld;
	Player& mPlayer;
public:
    GameState(StateStack& stack, Context context);
    virtual ~GameState();

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);
};

#endif // __GAMESTATE_HPP__