#pragma once
#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy(float x, float y);
	void update();
};