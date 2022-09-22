#include "Actor.h"
#include "Game.h"

Actor::Actor(std::string filename, float x, float y, int width, int height)
	:x(x), y(y), width(width), height(height), fileWidth(width), fileHeight(height)
{

	texture = Game::getTexture(filename);
}

void Actor::draw() {
	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = fileWidth;
	source.h = fileHeight;

	SDL_Rect destination;
	destination.x = x - width / 2;
	destination.y = y - height / 2;
	destination.w = width;
	destination.h = height;

	SDL_RenderCopyEx(Game::getRenderer(), texture, &source, &destination, 0, NULL, SDL_FLIP_NONE);
}

bool Actor::isOverlapping(Actor* actor) {
	if (actor->x - actor->width / 2 <= x + width / 2
		&& actor->x + actor->width / 2 >= x - width / 2
		&& actor->y + actor->height / 2 >= y - height / 2
		&& actor->y - actor->height / 2 <= y + height / 2)
	{
		return true;
	}
	return false;
}