/*
 * Game.hpp
 *
 *  Created on: 4 jun 2022
 *      Author: joe
 */

#ifndef INCLUDE_GAME_HPP_
#define INCLUDE_GAME_HPP_


#include <SFML/System/Time.hpp>
//#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../include/World.hpp"
#include "../include/Player.hpp"


class Game : private sf::NonCopyable {
public:
	Game();
	~Game();

	void run();

private:
	void processInput();
	void update(sf::Time elapsedTime);
	void render();

	void updateStatistics(sf::Time elapsedTime);
	// void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
	static const sf::Time	TimePerFrame;

	sf::RenderWindow mWindow;
	World mWorld;
	Player mPlayer;

	sf::Font mFont;
	sf::Text mStatisticsText;
	sf::Time mStatisticsUpdateTime;
	std::size_t mStatisticsNumFrames;

};

#endif /* INCLUDE_GAME_HPP_ */
