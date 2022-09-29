#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <unordered_map>

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

	static TTF_Font* getFont() {
		return getInstance().font;
	}

	static SDL_Texture* getTexture(std::string filename) {
		static std::unordered_map<std::string, SDL_Texture*> textures;

		auto entry = textures.find(filename);
		if (entry == textures.end()) {
			SDL_Surface* surface = IMG_Load(filename.c_str());
			SDL_Texture* texture = SDL_CreateTextureFromSurface(getRenderer(), surface);
			SDL_FreeSurface(surface);
			textures[filename] = texture;
		}

		return textures[filename];
	}

	void scale();
	bool scaledToMax = false;
	float scaleLower = 1.f;

	void loop();

	void start();

	bool loopActive = true;
	Layer* gameLayer;

	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
};