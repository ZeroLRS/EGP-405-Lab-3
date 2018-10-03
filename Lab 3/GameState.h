#pragma once

#include <vector>
#include "Entity.h"

class InputManager;

class GameState
{
public:
	GameState();
	~GameState();

	bool exit;
	std::vector<Entity*> entities;
	InputManager* input;
	void Update();
	void DrawMap();
	void HandleInput();
};

