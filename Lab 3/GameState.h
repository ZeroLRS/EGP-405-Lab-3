#pragma once

#include <vector>
#include "Entity.h"
#include "EventListener.h"

class InputManager;
class Player;

class GameState : public EventListener
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

	void handleEvent(const Event& _event) override;
	void initEvents();
	void movePlayer(Vector2 _direction);

	Player* getClientPlayer();
};

