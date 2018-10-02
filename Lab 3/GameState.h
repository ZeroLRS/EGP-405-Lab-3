#pragma once

#include <vector>
#include "Entity.h"

class GameState
{
public:
	GameState();
	~GameState();

	bool exit;
	std::vector<Entity*> entities;

	void Update();
	void DrawMap();
};

