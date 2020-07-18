#pragma once

#include "EventBase.h"
#include <vector>

struct SetTilemapEvent : public EventBase
{
	std::vector<std::vector<int>>* tilemap;
	std::vector<int>* blockedTiles;
};

struct InputEvent : public EventBase
{
	float moveX;
	float moveY;
	int e = 0;
};