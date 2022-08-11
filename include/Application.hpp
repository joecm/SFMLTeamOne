#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include "../include/ResourceHolder.hpp"
#include "../include/Player.hpp"
#include "../include/StateStack.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class Application {
public:
	Application();
	~Application();
	void run();

	void processInput();
	void update(sf::Time dt);
	void render();

	void updateStatistics(sf::Time dt);
	void registerStates();

private:
	static const sf::Time TimePerFrame;
	sf::RenderWindow mWindow;
	TextureHolder mTextures;
	FontHolder mFonts;
	Player	mPlayer;

	StateStack mStateStack;

	sf::Text mStatisticsText;
	sf::Time mStatisticsUpdateTime;
	std::size_t mStatisticsNumFrames;
};
#endif // __APPLICATION_HPP__