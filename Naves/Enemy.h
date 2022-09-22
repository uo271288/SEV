#pragma once
#include "Actor.h"
#include "Animation.h"

class Enemy : public Actor
{
public:
	Enemy(float x, float y);
	void update();
	void draw() override;

	Animation* aMoving;
	Animation* animation;
};