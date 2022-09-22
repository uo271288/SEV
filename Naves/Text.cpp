#include "Text.h"
#include "Game.h"
#include <SDL.h>

Text::Text(std::string content, float x, float y)
	:content(content), x(x), y(y) {

}

void Text::draw() {
	SDL_Color color{ 255,255,255,255 };

	SDL_Surface* surface = TTF_RenderText_Blended(Game::getFont(), content.c_str(), color);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::getRenderer(), surface);

	SDL_Rect rect{ x - surface->w / 2,y - surface->h / 2,surface->w,surface->h };

	SDL_FreeSurface(surface);
	SDL_RenderCopy(Game::getRenderer(), texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}