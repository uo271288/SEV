#include "Bomb.h"

Bomb::Bomb(float x, float y) :Actor("res/bomba.png", x, y, 40, 40) {
	vx = -1;
}

void Bomb::update() {
	x += vx;
}