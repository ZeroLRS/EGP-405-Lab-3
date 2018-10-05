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

#pragma once
#include"Entity.h"
#include <string>
#include "Utils.h"
class Player : public Entity
{
private:

	int collectedCoins;

public:
	Player() {};
	Player( Vector2 _startPos, bool _isClient);
	~Player();

	void addCoin();
	int getNumCoins();
	void move(Vector2 _direction);

	void setSymbol(char _symbol)
	{
		symbol = _symbol;
	}

	void setType(EntityType _type)
	{
		type = _type;
	}
};

