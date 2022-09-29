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
	void draw(int scrollX) override;
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

	State state = State::Moving;
	Orientation orientation = Orientation::Right;
};