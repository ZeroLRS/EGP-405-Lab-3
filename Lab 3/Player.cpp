/* File created by:
* Lucas Spiker and Cory Smith
* For:
* Lab 3 on 10/1/2018
* EGP-405 by Dan Buckstein
*
* “We certify that this work is entirely our own.
*	The assessor of this project may reproduce
*	this project and provide copies to other academic staff,
*	and/or communicate a copy of this project to a plagiarism-checking service,
*	which may retain a copy of the project on its database.”
*/

#include "Player.h"
#include "GameState.h"

Player::Player( Vector2 _startPos, bool _isClient):Entity(_startPos, (_isClient ? '@' : 'O'), (_isClient ? CLIENT_PLAYER : PLAYER))
{}


Player::~Player()
{}

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

