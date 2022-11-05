#pragma once
#include "Actor.h"

class Projectile : public Actor
{
public:
	Projectile(float x, float y);
	void update();

	float bounce;
};