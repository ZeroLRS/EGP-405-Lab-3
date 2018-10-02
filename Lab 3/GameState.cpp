#include "GameState.h"

GameState::GameState()
{
	exit = false;
}

GameState::~GameState()
{
}

void GameState::Update()
{
}

void GameState::DrawMap()
{
	system("cls");

	char map[20][10];

	// Fill the map with the empty character
	for (int x = 0; x < 20; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			map[x][y] = '.';
		}
	}

	for (const Entity* e : entities)
	{
		map[e->getPosition().x][e->getPosition().y] = e->getSymbol();
	}

	for (int x = 0; x < 20; x++)
	{
		for (int y = 0; y < 20; y++)
		{
			printf("%c", map[x][y]);
		}
		printf("\n");
	}

}
