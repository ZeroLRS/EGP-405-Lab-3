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
#include "Networking.h"

#include <thread>
#include <chrono>

const int FPS = 4;
const __int64 MS_PER_FRAME = 1000 / FPS;

void callHandlePackets(GameState* gs)
{
	while (!gs->exit)
		Networking::getInstance()->HandlePackets(gs);
}

int main(int const argc, char const *const *const argv)
{
	GameState* gs = new GameState();
	Networking* network = Networking::getInstance();
	network->init();

	std::thread networkThread(callHandlePackets, gs);

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

			lastTimeMS = currentTimeMS;
		}
	}

	networkThread.join();

	// exit
	printf("\n\n");
	system("pause");
	return 0;

}