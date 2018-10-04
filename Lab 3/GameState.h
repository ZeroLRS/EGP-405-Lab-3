#pragma once

#include <vector>
#include "Entity.h"
#include "EventListener.h"
#include "RakNet/NetworkIDObject.h"
#include "Player.h"

const int NUM_MAP_COLUMNS = 10;
const int NUM_MAP_ROWS = 20;

class InputManager;
//class Player;

class GameState : public EventListener
{
public:
	GameState();
	~GameState();

	bool exit;
	bool inGame;
	std::vector<Entity*> entities;
	InputManager* input;
	void Update();
	void DrawMap();
	void HandleInput();

	void handleEvent(const Event& _event) override;
	void initEvents();
	void movePlayer(Vector2 _direction, RakNet::NetworkID _playerID);
	void onCoinCollection(RakNet::NetworkID _coinID, RakNet::NetworkID _collectorID);
	void startGame(std::vector<Player> _players);
	void endGame();

	Player* getClientPlayer();
	Entity* getEntityByID(RakNet::NetworkID _ID);
};

