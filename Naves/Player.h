#pragma once

#include "Actor.h"
#include "Animation.h"
#include "Projectile.h"

class Player : public Actor
{
public:
	Player(float x, float y);
	Projectile* shoot();

	void update();
	void draw() override;
	void moveX(float direction);
	void moveY(float direction);

	int shootCadence = 30;
	int shootTime = 0;

	Animation* animation;
	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aRunningRight;
	Animation* aRunningLeft;
	Animation* aShootingRight;
	Animation* aShootingLeft;
};