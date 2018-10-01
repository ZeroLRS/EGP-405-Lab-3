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

int main(int const argc, char const *const *const argv)
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
	}
	while (returnEvent != nullptr);

	// exit
	printf("\n\n");
	system("pause");
	return 0;

}