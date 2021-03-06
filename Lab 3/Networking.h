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

#pragma once

#include "GameState.h"

#include "RakNet/RakPeerInterface.h"
#include "RakNet/MessageIdentifiers.h"
#include "RakNet/RakNetTypes.h"
#include "RakNet/BitStream.h"

#include <string>
#include <vector>
#include <mutex>

enum GameMessages
{
	ID_CUSTOM_MESSAGE_START = ID_USER_PACKET_ENUM,

	ID_GAME_MESSAGE_1,

	ID_GAME_MESSAGE_GAMESTATE,
	ID_GAME_MESSAGE_USERNAME_REQUEST,
	ID_GAME_MESSAGE_EVENT
};

#pragma pack(push, 1)
// Server broadcasted message to users
struct GameMessageData
{
	unsigned char typeID;

	// Max total packet size incl. typeID is 1KB
	char message[1023];

};
#pragma pack (pop)

#pragma pack(push, 1)
// Data from users
struct GameMessageFromUser
{
	unsigned char typeID;

	char playerName[16];
	char message[238];
	int messageSize;

};
#pragma pack (pop)

#pragma pack(push, 1)
// For when the user is first joining and requesting a name
struct GameMessageUsernameRequest
{
	unsigned char typeID;

	char playerName[16];
};
#pragma pack (pop)

struct userID
{
	std::string username;
	RakNet::RakNetGUID guid;
};

class Networking
{

private:
	RakNet::RakPeerInterface *peer;
	RakNet::Packet *packet;
	static Networking* instance;

public:
	Networking();
	~Networking();
	void HandlePackets(GameState* gs);
	void init();

	userID player1;
	userID player2;

	bool isServer;
	std::string username;
	
	static Networking* getInstance()
	{
		if (!instance)
		{
			instance = new Networking();
		}
		return instance;
	}

	// Template because there are a lot of event types we might want to send
	template<class T>
	void sendEventToServer(T* event)
	{
		GameMessageFromUser msg[1];
		msg->typeID = ID_GAME_MESSAGE_EVENT;

		strcpy_s(msg->playerName, username.c_str());
		msg->messageSize = sizeof(T);
		memcpy(msg->message, &event, sizeof(T));

		peer->Send((char *)msg, sizeof(GameMessageFromUser), HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->guid, false);
	}

	void gameStartup(GameState* gs);
	void sendNewCoins(GameState* gs);

};
