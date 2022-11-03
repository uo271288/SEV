#pragma once
#include "Actor.h"
#include "Animation.h"

class Enemy : public Actor
{
public:
	Enemy(std::string idle, std::string movement, std::string die, float x, float y);
	void update();
	void draw(int scrollX) override;
	void impacted();

	Animation* aMoving;
	Animation* aDying;
	Animation* animation;

	State state = State::Moving;

	int vxIntelligence;
};