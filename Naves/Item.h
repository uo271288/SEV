#pragma once

#include "Actor.h"
#include "Animation.h"

class Item : public Actor
{
public:
	Item(float x, float y, int gravity);
	void draw(int scrollX) override;
	void update();

	Animation* animation;
	int gravity;
};