#pragma once
#include "Actor.h"
#include "Animation.h"

class Enemy : public Actor
{
public:
	Enemy(std::string filename, float x, float y, int width, int height);
	virtual void update();
	void draw() override;

	Animation* aMoving;
	Animation* animation;
};