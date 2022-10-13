#pragma once

#include "Actor.h"

class Pad : public Actor
{
public:
	Pad(int x, int y);
	float getOrientation(float clickX);
};

