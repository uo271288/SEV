#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Layer.h"

#define WIDTH 480
#define HEIGHT 320

class Game
{
public:
	Game();

	static Game& getInstance()
	{
		static Game instance;
		return instance;
	}

	static SDL_Renderer* getRenderer() {
		return getInstance().renderer;
	}

	void scale();
	bool scaledToMax = false;
	float scaleLower = 1.f;

	void loop();

	bool loopActive = true;
	Layer* gameLayer;

	SDL_Window* window;
	SDL_Renderer* renderer;
};