#pragma once

#include <SDL_image.h>
#include <string>

class Actor
{
public:
	Actor(std::string filename, float x, float y, int width, int height);

	virtual void draw();

	bool isOverlapping(Actor* actor);

	float x, y, vx = 0, vy = 0;
	int width, height, fileWidth, fileHeight;
	SDL_Texture* texture;
};
