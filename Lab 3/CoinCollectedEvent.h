#pragma once
/* File created by:
* Lucas Spiker and Cory Smith
* For:
* Lab 3 on 10/1/2018
* EGP-405 by Dan Buckstein
*
* �We certify that this work is entirely our own.
*	The assessor of this project may reproduce
*	this project and provide copies to other academic staff,
*	and/or communicate a copy of this project to a plagiarism-checking service,
*	which may retain a copy of the project on its database.�
*/
#include "Event.h"
#include "RakNet/NetworkIDObject.h"

class CoinCollectedEvent :
	public Event
{
public:
	CoinCollectedEvent(RakNet::NetworkID _coinID, RakNet::NetworkID _collectorID);
	~CoinCollectedEvent();

	RakNet::NetworkID coinID;
	RakNet::NetworkID collectorID;

};

