#pragma once

#include "Utils.h"
#include "RakNet/NetworkIDObject.h"

class Entity : RakNet::NetworkIDObject
{
public:
	Entity();
	~Entity();

	Vector2 position;
	char symbol;
};
