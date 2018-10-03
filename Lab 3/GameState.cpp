#include "GameState.h"
#include "InputManager.h"
#include "EventSystem.h"
#include "PlayerMoveEvent.h"

GameState::GameState()
{
	exit = false;
	input = new InputManager();
}

GameState::~GameState()
{
	if (input)
	{
		delete input;
		input = nullptr;
	}
}

void GameState::Update()
{
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

	if (input->getKeyDown(VK_LEFT))
	{
		//move left
		PlayerMoveEvent playerMove(Vector2(-1, 0));
		EventSystem::getInstance()->addToEventQueue(playerMove);
	}
	if (input->getKeyDown(VK_UP))
	{
		//move up
		PlayerMoveEvent playerMove(Vector2(0, 1));
		EventSystem::getInstance()->addToEventQueue(playerMove);
	}
	if (input->getKeyDown(VK_RIGHT))
	{
		//move right
		PlayerMoveEvent playerMove(Vector2(1, 0));
		EventSystem::getInstance()->addToEventQueue(playerMove);
	}
	if (input->getKeyDown(VK_DOWN))
	{
		//move down
		PlayerMoveEvent playerMove(Vector2(0, -1));
		EventSystem::getInstance()->addToEventQueue(playerMove);
	}

	if (input->getKeyDown(VK_RETURN))
	{
		//ready up if out of game
	}
}
