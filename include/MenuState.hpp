#ifndef __MENUSTATE_HPP__
#define __MENUSTATE_HPP__

#include "../include/State.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class MenuState : public State {
private:
    enum OptionNames {
        Play,
        Exit
    };
    sf::Sprite mBackgroundSprite;
    std::vector<sf::Text> mOptions;
    std::size_t mOptionIndex;

public:
    MenuState(StateStack& stack, Context context);
    virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
    virtual ~MenuState();

	void updateOptionText();
};


#endif // __MENUSTATE_HPP__