#include "Networking.h"
#include "EventSystem.h"
#include "PlayerMoveEvent.h"
#include "CreatePlayerEvent.h"
#include "PlaceCoinEvent.h"

Networking::Networking()
{
	player1.username = "\n";
	player2.username = "\n";
}

Networking::~Networking()
{
	if (peer != nullptr)
	{
		RakNet::RakPeerInterface::DestroyInstance(peer);
	}
}

void Networking::init()
{
	// Networking
	const unsigned int bufferSz = 512;

	char str[bufferSz];

	// create and return instance of peer interface
	peer = RakNet::RakPeerInterface::GetInstance();

	// global peer settings for this app
	int isServer = 0;
	unsigned short serverPort = 60000;

	// ask user for peer type
	printf("(C)lient or (S)erver?\n");
	fgets(str, bufferSz, stdin);

	// start networking
	if ((str[0] == 'c') || (str[0] == 'C'))
	{
		RakNet::SocketDescriptor sd;
		peer->Startup(1, &sd, 1);


		printf("Enter username: (max 16 characters)\n");
		fgets(str, bufferSz, stdin);
		username = str;

		printf("Enter server IP or hit enter for 127.0.0.1\n");
		fgets(str, bufferSz, stdin);

		if (str[0] == '\n')
		{
			strcpy_s(str, "127.0.0.1");
		}

		printf("Starting the client.\n");
		peer->Connect(str, serverPort, 0, 0);
	}
	else
	{
		printf("Enter maximum number of clients: \n");
		fgets(str, bufferSz, stdin);

		unsigned int maxClients = atoi(str);
		RakNet::SocketDescriptor sd(serverPort, 0);
		peer->Startup(maxClients, &sd, 1);

		// We need to let the server accept incoming connections from the clients
		printf("Starting the server.\n");
		peer->SetMaximumIncomingConnections(maxClients);
		isServer = 1;
		username = "server";
	}

}



void Networking::gameStartup(GameState *gs)
{
	Player p1 = gs->createPlayerForPacket();
	Player p2 = gs->createPlayerForPacket();

	CreatePlayerEvent* p1e1 = new CreatePlayerEvent(p1, true);
	CreatePlayerEvent* p1e2 = new CreatePlayerEvent(p2, false);
	CreatePlayerEvent* p2e1 = new CreatePlayerEvent(p2, true);
	CreatePlayerEvent* p2e2 = new CreatePlayerEvent(p1, false);

	GameMessageFromUser msg[1];
	msg->typeID = ID_GAME_MESSAGE_EVENT;
	strcpy_s(msg->playerName, username.c_str());
	msg->messageSize = sizeof(CreatePlayerEvent);

	// Player1's character for Player1
	memcpy(msg->message, p1e1, sizeof(CreatePlayerEvent));
	peer->Send((char *)msg, sizeof(GameMessageFromUser), HIGH_PRIORITY, RELIABLE_ORDERED, 0, player1.guid, false);
	// Player2's character for Player1
	memcpy(msg->message, p1e2, sizeof(CreatePlayerEvent));
	peer->Send((char *)msg, sizeof(GameMessageFromUser), HIGH_PRIORITY, RELIABLE_ORDERED, 0, player1.guid, false);

	// Player2's character for Player2
	memcpy(msg->message, p2e1, sizeof(CreatePlayerEvent));
	peer->Send((char *)msg, sizeof(GameMessageFromUser), HIGH_PRIORITY, RELIABLE_ORDERED, 0, player1.guid, false);
	// Player2's character for Player1
	memcpy(msg->message, p2e2, sizeof(CreatePlayerEvent));
	peer->Send((char *)msg, sizeof(GameMessageFromUser), HIGH_PRIORITY, RELIABLE_ORDERED, 0, player1.guid, false);

	EventSystem::getInstance()->addToEventQueue(p1e1, true);
	EventSystem::getInstance()->addToEventQueue(p2e1, true);
}

void Networking::sendNewCoins(GameState * gs)
{
	for (int i = 0; i <= 5; i++)
	{
		Entity coin = gs->createCoinForPacket();
		PlaceCoinEvent* e = new PlaceCoinEvent(coin);

		GameMessageFromUser msg[1];
		msg->typeID = ID_GAME_MESSAGE_EVENT;
		strcpy_s(msg->playerName, username.c_str());
		msg->messageSize = sizeof(PlaceCoinEvent);

		memcpy(msg->message, e, sizeof(PlaceCoinEvent));

		peer->Send((char *)msg, sizeof(GameMessageFromUser), HIGH_PRIORITY, RELIABLE_ORDERED, 0, player1.guid, false);
		peer->Send((char *)msg, sizeof(GameMessageFromUser), HIGH_PRIORITY, RELIABLE_ORDERED, 0, player2.guid, false);
		EventSystem::getInstance()->addToEventQueue(e, true);
	}
}

void Networking::HandlePackets(GameState* gs)
{
	for (
		packet = peer->Receive();
		packet;
		peer->DeallocatePacket(packet), packet = peer->Receive()
		)
	{
		switch (packet->data[0])
		{
		case ID_REMOTE_DISCONNECTION_NOTIFICATION:
			printf("Another client has disconnected.\n");
			break;
		case ID_REMOTE_CONNECTION_LOST:
			printf("Another client has lost the connection.\n");
			break;
		case ID_REMOTE_NEW_INCOMING_CONNECTION:
			printf("Another client has connected.\n");
			break;
		case ID_CONNECTION_REQUEST_ACCEPTED:
			printf("Our connection request has been accepted.\n");
			{

				// Once the user has connected to the server, have them request a username
				GameMessageFromUser msg[1] = { ID_GAME_MESSAGE_USERNAME_REQUEST };
				strcpy_s(msg->playerName, username.c_str());

				peer->Send((char *)msg, sizeof(GameMessageFromUser), HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->guid, false);

			}
			break;
		case ID_GAME_MESSAGE_USERNAME_REQUEST:
		{
			GameMessageFromUser* usernameReq = (GameMessageFromUser*)packet->data;

			if (strcmp(usernameReq->playerName, player1.username.c_str())
				|| strcmp(usernameReq->playerName, player2.username.c_str())
					|| strcmp(usernameReq->playerName, username.c_str()))
			{
				peer->CloseConnection(packet->systemAddress, true);
				break;
			}

			userID newUser;
			newUser.username = usernameReq->playerName;
			newUser.guid = packet->guid;

			if (strcmp(player1.username.c_str(), "\n"))
			{
				player1 = newUser;
			}
			else
			{
				player2 = newUser;
			}

			printf("New user added");

		}
		break;
		case ID_NEW_INCOMING_CONNECTION:
			printf("A connection is incoming.\n");
			break;
		case ID_NO_FREE_INCOMING_CONNECTIONS:
			printf("The server is full.\n");
			break;
		case ID_DISCONNECTION_NOTIFICATION:
			if (isServer) {
				printf("A client has disconnected.\n");
			}
			else {
				printf("We have been disconnected.\n");
			}
			break;
		case ID_CONNECTION_LOST:
			if (isServer) {
				printf("A client lost the connection.\n");
			}
			else {
				printf("Connection lost.\n");
			}
			break;

		case ID_GAME_MESSAGE_1:
			printf("DEBUG MESSAGE: received packet ID_GAME_MESSAGE_1.\n");
			{
				//	RakNet::RakString rs;
				//	RakNet::BitStream bsIn(packet->data, packet->length, false);
				//	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
				//	bsIn.Read(rs);
				//	printf("%s\n", rs.C_String());

				// ****TO-DO: read packet without using bitstream

			}
			break;
		case ID_GAME_MESSAGE_GAMESTATE:
		{
			GameMessageData* msg = (GameMessageData*)packet->data;
			system("cls");
			printf("%s", msg->message);
		}
		break;
		case ID_GAME_MESSAGE_EVENT:
		{
			// Parse the packet data into our struct
			GameMessageFromUser* msg = (GameMessageFromUser*) packet->data;

			// If we're the server, send this event to the other player as well
			if (isServer)
			{
				RakNet::RakNetGUID otherUser;

				if (packet->guid == player1.guid)
				{
					otherUser = player2.guid;
				}
				else
				{
					otherUser = player1.guid;
				}

				peer->Send((char*)msg, sizeof(GameMessageData), HIGH_PRIORITY, RELIABLE, 0, otherUser, false);

			}

			// If we're either, get the event from the message and then add it to the event queue
			Event* event = (Event*) malloc(msg->messageSize);
			memcpy(&event, msg->message, msg->messageSize);
			EventSystem::getInstance()->addToEventQueue(event, true);
			
		}
		break;
		default:
			printf("Message with identifier %i has arrived.\n", packet->data[0]);
			break;
		}
	}
}

Networking* Networking::instance = 0;