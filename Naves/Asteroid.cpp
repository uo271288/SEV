#include "Asteroid.h"

Asteroid::Asteroid(std::string filename, float x, float y, int width, int height)
	: Enemy(filename, x, y, width, height) {
	aMoving = new Animation(filename, width, height, 151, 51, 6, 3);
	animation = aMoving;
	vy = -1;
}

void Asteroid::update() {
	animation->update();
	y += vy;
}