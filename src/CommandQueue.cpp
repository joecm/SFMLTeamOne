/*
 * CommandQueue.cpp
 *
 *  Created on: 6 dic 2021
 *      Author: joe
 */

#include "../include/CommandQueue.hpp"
//#include "../include/SceneNode.hpp"

void CommandQueue::push(const Command& command)
{
	mQueue.push(command);
}

Command CommandQueue::pop()
{
	Command command = mQueue.front();
	mQueue.pop();
	return command;
}

bool CommandQueue::isEmpty() const
{
	return mQueue.empty();
}


