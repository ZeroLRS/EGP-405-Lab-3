#include "GameState.h"
#include "InputManager.h"
#include "EventSystem.h"
#include "PlayerMoveEvent.h"
#include "Player.h"
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

void GameState::movePlayer(Vector2 _direction)
{
	getClientPlayer()->move(_direction);

	printf("(%i , %i)", _direction.x, _direction.y);
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

void GameState::Update()
{
	//dispatch events from queue
	EventSystem::getInstance()->dispatchEvents();
	HandleInput();
}

void GameState::DrawMap()
{
	system("cls");

	char map[10][20];

	// Fill the map with the empty character
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 20; y++)
		{
			map[x][y] = '.';
		}
	}

	for (const Entity* e : entities)
	{
		map[e->getPosition().x][e->getPosition().y] = e->getSymbol();
	}

	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 20; y++)
		{
			printf("%c", map[x][y]);
		}
		printf("\n");
	}

}

void GameState::HandleInput()
{
	input->updateKeyStates();

	if (input->getKey(VK_LEFT))
	{
		//move left
		PlayerMoveEvent* playerMove = new PlayerMoveEvent(Vector2(-1, 0));
		EventSystem::getInstance()->addToEventQueue(playerMove);
	}
	if (input->getKeyDown(VK_UP))
	{
		//move up
		PlayerMoveEvent* playerMove = new PlayerMoveEvent(Vector2(0, 1));
		EventSystem::getInstance()->addToEventQueue(playerMove);
	}
	if (input->getKeyDown(VK_RIGHT))
	{
		//move right
		PlayerMoveEvent* playerMove = new PlayerMoveEvent(Vector2(1, 0));
		EventSystem::getInstance()->addToEventQueue(playerMove);
	}
	if (input->getKeyDown(VK_DOWN))
	{
		//move down
		PlayerMoveEvent* playerMove = new PlayerMoveEvent(Vector2(0, -1));
		EventSystem::getInstance()->addToEventQueue(playerMove);
	}

	if (input->getKeyDown(VK_RETURN))
	{
		//ready up if out of game
	}
}

void GameState::handleEvent(const Event & _event)
{
	switch (_event.type)
	{
		case PLAYER_MOVE:
		{
			movePlayer(((const PlayerMoveEvent &)_event).moveDirection);
			break;
		}
		default:
			return;
	}
}