#pragma once

#include "Utils.h"
#include "RakNet/NetworkIDObject.h"

class Entity : RakNet::NetworkIDObject
{
public:
	Entity(Vector2 _startPos, char _symbol);
	~Entity();

	Vector2 getPosition() { return position; };
	char getSymbol() { return symbol; };

private:
	Vector2 position;
	char symbol;
};
