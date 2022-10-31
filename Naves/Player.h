#pragma once

#include "Actor.h"
#include "Projectile.h"
#include "Game.h"

class Player : public Actor
{
public:
	Player(float x, float y);
	Projectile* shoot();
	
	void update();
	void moveX(float direction);
	void moveY(float direction);

	void changeShip(int ship);

	int shootCadence = 30;
	int shootTime = 0;
	float speed = 3.;
};