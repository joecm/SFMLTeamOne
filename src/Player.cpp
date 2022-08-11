/*
 * Player.cpp
 *
 *  Created on: 26 jun 2022
 *      Author: joe
 */

#include "../include/Player.hpp"
#include "../include/Aircraft.hpp"
#include "../include/CommandQueue.hpp"
#include <iostream>
#include <string>
#include <algorithm>

struct AircraftMover
{
	sf::Vector2f velocity;

	AircraftMover(float vx, float vy)
	: velocity(vx, vy)
	{
	}
	//void operator() (SceneNode& node, sf::Time) const
	void operator() (Aircraft& aircraft, sf::Time) const
	{
		//Aircraft& aircraft = static_cast<Aircraft&>(node);
		aircraft.accelerate(velocity);
		// aircraft.setVelocity(aircraft.getVelocity()+velocity);
	}
};

Player::Player() {
	// TODO Auto-generated constructor stub
	// Set initial key bindings
	mKeyBinding[sf::Keyboard::Left] = Action::MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = Action::MoveRight;
	mKeyBinding[sf::Keyboard::Up] = Action::MoveUp;
	mKeyBinding[sf::Keyboard::Down] = Action::MoveDown;
	// voy a crear un event
	mKeyBinding[sf::Keyboard::P] = Action::Position;

	// Set initial action bindings
	initializeActions();

	// Assign all categories to player's aircraft
	for (auto& pair : mActionBinding)
		pair.second.category = Category::PlayerAircraft;
}

void Player::initializeActions() {
	const float playerSpeed = 200.f;

	mActionBinding[Action::MoveLeft].action	 = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
	mActionBinding[Action::MoveRight].action = derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f));
	mActionBinding[Action::MoveUp].action    = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
	mActionBinding[Action::MoveDown].action  = derivedAction<Aircraft>(AircraftMover(0.f, +playerSpeed));

	// Binding para el event con un binding y una lambda
	mActionBinding[Action::Position].action = [] (SceneNode& s, sf::Time) {
		std::cout << s.getPosition().x <<","
				  << s.getPosition().y << "\n";
	};
}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands){
	if (event.type == sf::Event::KeyPressed) {
		// Check if pressed key appears in the key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
					commands.push(mActionBinding[found->second]);
	}


	/*if (event.type == sf::Event::KeyPressed
				&& event.key.code == sf::Keyboard::P) {
		Command output;
		output.category = Category::PlayerAircraft;
		output.action = [] (SceneNode& s, sf::Time) {
				std::cout << s.getPosition().x <<","
						  << s.getPosition().y << "\n";
		};
		commands.push(output);
	}*/
}


void Player::handleRealtimeInput(CommandQueue& commands) {
/*	const float playerSpeed =30.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		Command moveleft;
		moveleft.category = Category::PlayerAircraft;
		moveleft.action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
		commands.push(moveleft);
	}*/
	for (auto pair : mKeyBinding) {
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

bool Player::isRealtimeAction(Action action) {
	switch (action)
	{
		case Action::MoveLeft:
		case Action::MoveRight:
		case Action::MoveDown:
		case Action::MoveUp:
		case Action::Position: // event
			return true;

		default:
			return false;
	}
}
