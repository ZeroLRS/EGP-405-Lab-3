#pragma once

#include "GameState.h"

#include "RakNet/RakPeerInterface.h"
#include "RakNet/MessageIdentifiers.h"
#include "RakNet/RakNetTypes.h"
#include "RakNet/BitStream.h"

#include <string>
#include <vector>

enum GameMessages
{
	ID_CUSTOM_MESSAGE_START = ID_USER_PACKET_ENUM,

	ID_GAME_MESSAGE_1,

	ID_GAME_MESSAGE_GAMESTATE,
	ID_GAME_MESSAGE_USERNAME_REQUEST,
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
	void deinit();

	std::vector<userID> users;
	bool isServer;
	std::string username;
	
	static Networking* getInstance() { return instance; }

};
