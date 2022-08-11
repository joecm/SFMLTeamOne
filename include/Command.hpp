/*
 * Command.hpp
 *
 *  Created on: 20 jun 2022
 *      Author: joe
 */

#ifndef INCLUDE_COMMAND_HPP_
#define INCLUDE_COMMAND_HPP_


#include <SFML/System/Time.hpp>
#include <functional>
#include "../include/Category.hpp"
#include <cassert>

class SceneNode;

struct Command {
	Command();
	std::function<void(SceneNode&, sf::Time)> action;
	unsigned int category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn) {
	return [=] (SceneNode& node, sf::Time dt) {

		// Check if cast is safe
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		// Downcast node and invoke function on it
		fn(static_cast<GameObject&>(node), dt);
	};
}

#endif /* INCLUDE_COMMAND_HPP_ */
