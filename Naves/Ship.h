#pragma once

#include "Enemy.h"

class Ship : public Enemy
{
public:
	Ship(std::string filename, float x, float y, int width, int height);
	void update() override;
};