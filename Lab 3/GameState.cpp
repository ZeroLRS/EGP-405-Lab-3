#include "GameState.h"
#include "InputManager.h"
#include "EventSystem.h"
#include "PlayerMoveEvent.h"
#include "Player.h"
#include "GameEndEvent.h"
#include "CoinCollectedEvent.h"
#include "GameStartEvent.h"
#include <string>
#include <random>
#include <algorithm>
GameState::GameState()
{
	exit = false;
	input = new InputManager();

	initEvents();
}

GameState::~GameState()
{
	if (input)
	{
		delete input;
		input = nullptr;
	}
}

void GameState::initEvents()
{
	//init all events gamestate should listen to
	EventSystem::getInstance()->addListener(this, PLAYER_MOVE);
}

void GameState::movePlayer(Vector2 _direction, RakNet::NetworkID _playerID)
{
	Player* player = (Player*)getEntityByID(_playerID);//->move(_direction);

	if (!player)
		return;

	player->move(_direction);

	printf("(%i , %i)", _direction.x, _direction.y);
}

void GameState::onCoinCollection(RakNet::NetworkID _coinID, RakNet::NetworkID _collectorID)
{
	Player* collector = nullptr;
	auto coinLocation = entities.begin();

	bool foundCollector = false;
	bool foundCoin = false;

	for (auto iter = entities.begin(); iter != entities.end(); ++iter)
	{
		if (!foundCollector && (*iter)->GetNetworkID() == _collectorID)
		{
			collector = (Player*)(*iter);
			foundCollector = true;
		}
		else if (!foundCoin && (*iter)->GetNetworkID() == _coinID)
		{
			coinLocation = iter;
			foundCoin = true;
		}
		else if (foundCoin && foundCollector)
		{
			break;
		}
	}

	if (!foundCoin || !foundCollector)
		return;

	entities.erase(coinLocation);

	collector->addCoin();

	//TODO: MOVE THIS TO SERVER
	if (collector->getNumCoins() >= 3)
	{
		//End game if player has 3 coins
		GameEndEvent gameOver(collector->GetNetworkID());

		EventSystem::getInstance()->addToEventQueue(&gameOver);
	}
}

//initialize the array of entities w/ the new players
void GameState::startGame(std::vector<Player> _players)
{
	RakNet::NetworkID playerID = getClientPlayer()->GetNetworkID();

	for (auto iter = _players.begin(); iter != _players.end(); ++iter)
	{
		if ((*iter).GetNetworkID() == playerID)
			continue;

		entities.push_back(&(*iter));
	}

	inGame = true;
}

void GameState::endGame()
{
	inGame = false;
}

//TODO: MOVE THIS TO SERVER
void GameState::spawnCoins()
{
	int numToSpawn = 5;
	bool usedSlots[NUM_MAP_COLUMNS][NUM_MAP_ROWS]{ { false }, {false} };

	while (numToSpawn > 0)
	{
		int randX = std::rand() % NUM_MAP_COLUMNS;
		int randY = std::rand() % NUM_MAP_ROWS;

		if (!usedSlots[randX][randY])
		{
			//TODO: SPAWN COIN HERE
			--numToSpawn;
			
			usedSlots[randX][randY] = true;
		}
	}
}

//TODO: MOVE THIS TO SERVER
void GameState::checkForCoinCollisions()
{
	for (auto playerIter = entities.begin(); playerIter != entities.end(); ++playerIter)
	{
		//if playerIter entity is not a player
		if (!(*playerIter)->getType() != PLAYER && !(*playerIter)->getType() != CLIENT_PLAYER)
			continue;

		for (auto coinIter = entities.begin(); coinIter != entities.end(); ++coinIter)
		{
			//if coinIter entity is a player
			if ((*coinIter)->getType() == PLAYER || (*coinIter)->getType() == CLIENT_PLAYER)
				continue;

			Vector2 playerPos = (*playerIter)->getPosition();
			Vector2 coinPos = (*coinIter)->getPosition();

			if (playerPos.x == coinPos.x && playerPos.y == coinPos.y)
			{
				//TODO: SEND COIN COLLECTION PACKET
			}
		}
	}
}

Player* GameState::getClientPlayer()
{
	for (auto iter = entities.begin(); iter != entities.end(); ++iter)
	{
		if ((*iter)->getType() == CLIENT_PLAYER)
		{
			return (Player*)(*iter);
		}
	}

	return nullptr;
}

Entity* GameState::getEntityByID(RakNet::NetworkID _ID)
{
	for (auto iter = entities.begin(); iter != entities.end(); ++iter)
	{
		if ((*iter)->GetNetworkID() == _ID)
		{
			return *iter;
		}
	}

	return nullptr;
}


void GameState::Update()
{
	//dispatch events from queue
	EventSystem::getInstance()->dispatchEvents();
	HandleInput();
}

void GameState::DrawMap()
{
	system("cls");


	// player1name (coincount) vs player2 (1) vs player3 (2) vs...
	for (int i = 0; i < entities.size(); ++i)
	{
		//if current entity is not a player
		if (entities[i]->getType() != PLAYER && entities[i]->getType() != CLIENT_PLAYER)
			continue;

		printf( ( ((Player*)entities[i])->getUserName() + " (%i)" ).c_str(), ((Player*)entities[i])->getNumCoins());

		if (i < entities.size() - 1)
		{
			printf(" V.S ");
		}
		else
		{
			printf("\n");
		}

	}

	char map[NUM_MAP_COLUMNS][NUM_MAP_ROWS];

	// Fill the map with the empty character
	for (int x = 0; x < NUM_MAP_COLUMNS; x++)
	{
		for (int y = 0; y < NUM_MAP_ROWS; y++)
		{
			map[x][y] = '.';
		}
	}

	for (const Entity* e : entities)
	{
		map[e->getPosition().x][e->getPosition().y] = e->getSymbol();
	}

	for (int x = 0; x < NUM_MAP_COLUMNS; x++)
	{
		for (int y = 0; y < NUM_MAP_ROWS; y++)
		{
			printf("%c", map[x][y]);
		}
		printf("\n");
	}

	printf("3 coins to win! \n");

}

void GameState::HandleInput()
{
	input->updateKeyStates();

	if (inGame) // during game input
	{
		if (input->getKey(VK_LEFT))
		{
			//move left
			PlayerMoveEvent* playerMove = new PlayerMoveEvent(Vector2(-1, 0), getClientPlayer()->GetNetworkID());
			EventSystem::getInstance()->addToEventQueue(playerMove);
		}
		if (input->getKeyDown(VK_UP))
		{
			//move up
			PlayerMoveEvent* playerMove = new PlayerMoveEvent(Vector2(0, 1), getClientPlayer()->GetNetworkID());
			EventSystem::getInstance()->addToEventQueue(playerMove);
		}
		if (input->getKeyDown(VK_RIGHT))
		{
			//move right
			PlayerMoveEvent* playerMove = new PlayerMoveEvent(Vector2(1, 0), getClientPlayer()->GetNetworkID());
			EventSystem::getInstance()->addToEventQueue(playerMove);
		}
		if (input->getKeyDown(VK_DOWN))
		{
			//move down
			PlayerMoveEvent* playerMove = new PlayerMoveEvent(Vector2(0, -1), getClientPlayer()->GetNetworkID());
			EventSystem::getInstance()->addToEventQueue(playerMove);
		}
	}
	else // out of game input
	{
		if (input->getKeyDown(VK_RETURN))
		{
			//ready up if out of game
		}
	}
}

void GameState::handleEvent(const Event & _event)
{
	switch (_event.type)
	{
	case GAME_START:
	{
		const GameStartEvent gameStart = (const GameStartEvent &)_event;
		
		startGame(gameStart.playersInMatch);
		break;
	}
	case GAME_END:
	{
		endGame();
		break;
	}
	case COIN_COLLECTED:
	{
		const CoinCollectedEvent coinCollected = (const CoinCollectedEvent &)_event;
		
		onCoinCollection(coinCollected.coinID, coinCollected.collectorID);
		break;
	}
	case PLAYER_MOVE:
	{
		const PlayerMoveEvent moveEvent = ((const PlayerMoveEvent &)_event);

		movePlayer(moveEvent.moveDirection, moveEvent.playerID);
		break;
	}
	default:
		return;
	}
}