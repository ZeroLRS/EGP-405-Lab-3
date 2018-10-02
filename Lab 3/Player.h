#pragma once
#include"Entity.h"
#include <string>

class Player : public Entity
{
private:

	std::string userName;
	int collectedCoins;

public:
	Player(std::string _username, Vector2 _startPos, bool _isClient);
	~Player();

	std::string getUserName();

	void addCoin();
	int getNumCoins();
};

