#pragma once

#include "Actor.h"
#include "Projectile.h"

class Player : public Actor
{
public:
	Player(float x, float y);
	Projectile* shoot();
	
	void update();
	void moveX(float direction);
	void moveY(float direction);

	int shootCadence = 30;
	int shootTime = 0;
};