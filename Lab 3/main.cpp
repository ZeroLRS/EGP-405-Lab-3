/* File created by:
 * Lucas Spiker and Cory Smith
 * For:
 * Lab 3 on 10/1/2018
 * EGP-405 by Dan Buckstein
 *
 * “We certify that this work is entirely our own.
 *	The assessor of this project may reproduce
 *	this project and provide copies to other academic staff, 
 *	and/or communicate a copy of this project to a plagiarism-checking service,
 *	which may retain a copy of the project on its database.”
 */

// RakNet includes
#include "RakNet/RakPeerInterface.h"
#include "RakNet/MessageIdentifiers.h"
#include "RakNet/RakNetTypes.h"
#include "RakNet/BitStream.h"

// Our includes
#include "Event.h"
#include "EventQueue.h"
#include "GameState.h"

#include <chrono>
#include <thread>
#include <mutex>

const int FPS = 5;
const __int64 MS_PER_FRAME = 1000 / FPS;

// Test mutex
std::mutex queueThreadLock;

void addStuffToQueue(EventQueue* queue)
{
	for (int i = 0; i < 100; i++)
	{
		{
			std::lock_guard<std::mutex> lock(queueThreadLock);

			Event* testEvent = new Event();
			testEvent->TestString = "Hello World";
			queue->push(testEvent);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void emptyQueue(EventQueue* queue)
{
	std::lock_guard<std::mutex> lock(queueThreadLock);

	Event* currEvent = queue->pop();

	while (currEvent != nullptr)
	{
		printf("%s", currEvent->TestString.c_str());
		delete(currEvent);
		currEvent = queue->pop();
	}
}

int main(int const argc, char const *const *const argv)
{
	GameState* gs = new GameState();

	// Thread testing
	EventQueue* queue = new EventQueue(); // Test queue for multithreading
	std::thread testThread(addStuffToQueue, queue);

	auto lastTime = std::chrono::system_clock::now();
	auto lastTimeMS = std::chrono::time_point_cast<std::chrono::milliseconds>(lastTime);

	while (!gs->exit)
	{

		auto currentTime = std::chrono::system_clock::now();
		auto currentTimeMS = std::chrono::time_point_cast<std::chrono::milliseconds>(currentTime);

		auto elapsedChronoTime = currentTimeMS - lastTimeMS;

		__int64 elapsedTime = elapsedChronoTime.count();

		if (elapsedTime > MS_PER_FRAME)
		{
			gs->Update();
			gs->DrawMap();
			emptyQueue(queue);

			lastTimeMS = currentTimeMS;
		}
	}

	// Make sure thread is done
	testThread.join();

	// exit
	printf("\n\n");
	system("pause");
	return 0;

}

void TestQueue()
{
	// Testing the queue
	EventQueue* queue = new EventQueue();

	Event* ev2 = new Event();
	Event* ev3 = new Event();
	Event* ev1 = new Event();
	Event* returnEvent = nullptr;

	ev1->TestString = "Hello1\n";
	ev2->TestString = "Hello2\n";
	ev3->TestString = "Hello3\n";

	queue->push(ev1);
	queue->push(ev2);
	queue->push(ev3);

	returnEvent = queue->pop();

	do
	{
		printf("%s", returnEvent->TestString.c_str());
		delete(returnEvent);
		returnEvent = queue->pop();
	} while (returnEvent != nullptr);
}