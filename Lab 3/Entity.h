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

#include "Utils.h"
#include "RakNet/NetworkIDObject.h"

enum EntityType
{
	DEFAULT_ENTITY = -1,
	CLIENT_PLAYER,
	PLAYER,
	COIN
};

class Entity : public RakNet::NetworkIDObject
{
public:
	Entity() {};
	Entity(Vector2 _startPos, char _symbol, EntityType _type);
	~Entity();

	Vector2 getPosition() const { return position; };
	char getSymbol() const { return symbol; };
	EntityType getType() const { return type; };

protected:
	Vector2 position;
	char symbol;
	EntityType type;
};
