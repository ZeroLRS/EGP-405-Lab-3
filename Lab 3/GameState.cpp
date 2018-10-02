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

	char map[20][20];

	// Fill the map with the empty character
	for (int x = 0; x < 20; x++)
	{
		for (int y = 0; y < 20; y++)
		{
			map[x][y] = '.';
		}
	}

	for (const Entity* e : entities)
	{
		map[e->position.x][e->position.y] = e->symbol;
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
