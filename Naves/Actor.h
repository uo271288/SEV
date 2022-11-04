#pragma once

#include <SDL_image.h>
#include <string>

#include "BoundingBox.h"

enum class Orientation {
	Right, Left
};

enum class State {
	Moving, Jumping, Dying, Dead, Shooting
};

class Actor
{
public:
	Actor(std::string filename, float x, float y, int width, int height);

	virtual void draw(int scrollX = 0, int scrollY = 0);

	bool isOverlapping(Actor* actor);
	bool containsPoint(int pointX, int pointY);

	bool clicked = false;

	float x, y;
	int vx, vy;
	int width, height, fileWidth, fileHeight;
	SDL_Texture* texture;

	void sweep(std::unordered_set <Actor*>& actors);

	BoundingBox boundingBox;
};
