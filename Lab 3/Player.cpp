#include "Player.h"
#include "GameState.h"

Player::Player(std::string _userName, Vector2 _startPos, bool _isClient):Entity(_startPos, (_isClient ? '@' : 'O'), (_isClient ? CLIENT_PLAYER : PLAYER)), 
userName(_userName)
{}


Player::~Player()
{}

std::string Player::getUserName()
{
	return userName;
}

void Player::addCoin() 
{ 
	++collectedCoins; 
};


int Player::getNumCoins() 
{ 
	return collectedCoins; 
};

void Player::move(Vector2 _direction)
{
	position.x += _direction.x;
	position.y += _direction.y;

	if (position.x < 0)
	{
		position.x = 0;
	}
	else if (position.x >= NUM_MAP_COLUMNS)
	{
		position.x = NUM_MAP_COLUMNS - 1;
	}

	if (position.y < 0)
	{
		position.y = 0;
	}
	else if (position.y >= NUM_MAP_ROWS)
	{
		position.y = NUM_MAP_ROWS - 1;
	}

	//TODO: SEND UPDATE PLAYER POSITION PACKET
}

