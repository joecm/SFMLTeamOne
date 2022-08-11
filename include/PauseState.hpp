#ifndef __PAUSESTATE_H__
#define __PAUSESTATE_H__

#include "../include/State.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class PauseState : public State {
public:
	PauseState(StateStack& stack, Context context);
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
    virtual ~PauseState();

private:
	sf::Sprite mBackgroundSprite;
	sf::Text mPausedText;
	sf::Text mInstructionText;
};

#endif // __PAUSESTATE_H__