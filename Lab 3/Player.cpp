#include "Player.h"



Player::Player(std::string _userName, Vector2 _startPos, bool _isClient):Entity(_startPos, (_isClient ? '@' : 'O')), userName(_userName)
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