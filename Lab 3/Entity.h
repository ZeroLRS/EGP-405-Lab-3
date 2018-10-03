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

class Entity : RakNet::NetworkIDObject
{
public:
	Entity(Vector2 _startPos, char _symbol, EntityType _type);
	~Entity();

	Vector2 getPosition() const { return position; };
	char getSymbol() const { return symbol; };
	EntityType getType() const { return type; };

private:
	Vector2 position;
	char symbol;
	EntityType type;
};
