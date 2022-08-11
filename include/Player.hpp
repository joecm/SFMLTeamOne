/*
 * Player.hpp
 *
 *  Created on: 26 jun 2022
 *      Author: joe
 */

#ifndef INCLUDE_PLAYER_HPP_
#define INCLUDE_PLAYER_HPP_

#include <SFML/Window/Event.hpp>
#include <map>
#include "../include/Command.hpp"

class CommandQueue;

class Player {
public:
	enum class Action {
				MoveLeft,
				MoveRight,
				MoveUp,
				MoveDown,
				Position,
				ActionCount
	};
	Player();
	~Player();
	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);
	void assignKey (Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key getAssignedKey (Action action) const;
private:
	static bool isRealtimeAction(Action action);
	void initializeActions();

private:
	std::map<sf::Keyboard::Key, Action> mKeyBinding;
	std::map<Action, Command> mActionBinding;

};

#endif /* INCLUDE_PLAYER_HPP_ */
