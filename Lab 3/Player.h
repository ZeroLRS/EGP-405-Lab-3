#pragma once
#include"Entity.h"
#include <string>
#include "Utils.h"
class Player : public Entity
{
private:

	int collectedCoins;

public:
	Player( Vector2 _startPos, bool _isClient);
	~Player();

	void addCoin();
	int getNumCoins();
	void move(Vector2 _direction);
};

