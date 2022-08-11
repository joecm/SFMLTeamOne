/*
 * CommandQueue.hpp
 *	Transportar commands al mundo y al grafo de escena
 *
 *  Created on: 6 dic 2021
 *      Author: joe
 */

#ifndef INCLUDE_BOOK_COMMANDQUEUE_HPP_
#define INCLUDE_BOOK_COMMANDQUEUE_HPP_

#include "../include/Command.hpp"
#include <queue>

class CommandQueue
{
public:
	void push(const Command& command);
	Command pop();
	bool isEmpty() const;

private:
	std::queue<Command>	mQueue;
};
#endif /* INCLUDE_BOOK_COMMANDQUEUE_HPP_ */
