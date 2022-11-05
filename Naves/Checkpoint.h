#pragma once

#include "Actor.h"
#include "Animation.h"

class Checkpoint : public Actor {
public:
	Checkpoint(float x, float y);

	void draw(int scrollX, int scrolY) override;
	void update();

	Animation* animation;
};