#ifndef __TITLESTATE_HPP__
#define __TITLESTATE_HPP__

#include "../include/State.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class TitleState : public State
{
private:
    sf::Sprite mBackgroundSprite;
	sf::Text mText;

	bool mShowText;
	sf::Time mTextEffectTime;
public:
    TitleState(StateStack& stack, Context context);
    virtual ~TitleState();

    virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
};

#endif // __TITLESTATE_HPP__