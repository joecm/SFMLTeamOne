#ifndef __PARALLELTASK_H__
#define __PARALLELTASK_H__

#include <SFML/System/Thread.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Lock.hpp>
#include <SFML/System/Clock.hpp>

class ParallelTask {
public:
	ParallelTask();
	void execute();
	bool isFinished();
	float getCompletion();
private:
	void runTask();
	sf::Thread mThread;
	bool mFinished;
	sf::Clock mElapsedTime;
	sf::Mutex mMutex;
};

#endif // __PARALLELTASK_H__