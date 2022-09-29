#pragma once

#include "Actor.h"

class Tile :public Actor
{
public:
	Tile(std::string filename, int x, int y);
};