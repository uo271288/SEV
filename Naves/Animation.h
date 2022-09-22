#pragma once

#include <string>
#include <SDL.h>
class Animation
{
public:
	Animation(std::string filename, int actorWidth, int actorHeight, int fileWidth,
		int fileHeight, int updateFrequency, int totalFrames, bool loop);

	bool update();
	void draw(float x, float y);

	int actorWidth, actorHeight, fileWidth,
		fileHeight, frameWidth, frameHeight;
	int totalFrames, currentFrame = 0;
	int updateFrequency, updateTime = 0;
	bool loop = false;

	SDL_Texture* texture;
	SDL_Rect source;
};