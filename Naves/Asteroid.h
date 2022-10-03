#pragma once
#include "Enemy.h"
class Asteroid :
    public Enemy
{
public:
	Asteroid(std::string filename, float x, float y, int width, int height);
	void update() override;
};