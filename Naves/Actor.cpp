#include "Actor.h"
#include "Game.h"

Actor::Actor(std::string filename, float x, float y, int width, int height)
	:x(x), y(y), width(width), height(height), fileWidth(width), fileHeight(height),
	vx(0), vy(0), boundingBox(x, y, width, height)
{

	texture = Game::getTexture(filename);
}

void Actor::draw(int scrollX) {
	SDL_Rect source{
	source.x = 0,
	source.y = 0,
	source.w = fileWidth,
	source.h = fileHeight };

	SDL_Rect destination;
	destination.x = x - width / 2 - scrollX;
	destination.y = y - height / 2;
	destination.w = width;
	destination.h = height;

	SDL_RenderCopyEx(Game::getRenderer(), texture, &source, &destination, 0, NULL, SDL_FLIP_NONE);
}

bool Actor::isOverlapping(Actor* actor) {
	return boundingBox.overlaps(actor->boundingBox);
}

bool Actor::containsPoint(int pointX, int pointY) 
{
	return boundingBox.contains(pointX, pointY);
}

void Actor::sweep(std::unordered_set <Actor*>& actors) {
	Vector2d delta{ vx,vy };

	delta = boundingBox.sweep(actors, delta);
	vx = delta.x;
	vy = delta.y;
	x += vx;
	y += vy;
}