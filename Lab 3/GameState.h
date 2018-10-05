#pragma once

#include <vector>
#include "Entity.h"
#include "EventListener.h"
#include "RakNet/NetworkIDObject.h"
#include "Player.h"
#include "RakNet/NetworkIDManager.h"

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
	std::string latestMessage;
	std::vector<Entity*> entities;
	InputManager* input;
	RakNet::NetworkIDManager idManager;

	void Update();
	void DrawMap();
	void HandleInput();

	void handleEvent(const Event& _event) override;
	void initEvents();
	void movePlayer(Vector2 _direction, RakNet::NetworkID _playerID);
	void onCoinCollection(RakNet::NetworkID _coinID, RakNet::NetworkID _collectorID);
	void startGame(std::vector<Entity> coins);//, Vector2 _otherPlayerPos);
	void endGame();
	void spawnCoins(int _numSpawns);
	void addEntity(Entity* _entity);
	void deleteAllCoins();
	void createPlayerFromPacket(Player _playerData, bool _isClient);
	Player createPlayerForPacket();

	void placeCoin(Entity coin);


	void checkForCoinCollisions();
	Player* getClientPlayer();
	Entity* getEntityByID(RakNet::NetworkID _ID);
};

