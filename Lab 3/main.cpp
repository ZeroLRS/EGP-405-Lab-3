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

const int FPS = 4;
const __int64 MS_PER_FRAME = 1000 / FPS;

int main(int const argc, char const *const *const argv)
{
	GameState* gs = new GameState();
	Networking* network = Networking::getInstance();
	network->init();

	

	// exit
	printf("\n\n");
	system("pause");
	return 0;

}