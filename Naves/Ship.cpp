#include "Ship.h"

Ship::Ship(std::string filename, float x, float y, int width, int height) 
	: Enemy(filename, x, y, width, height){
	aMoving = new Animation(filename, width, height, 108, 40, 6, 3);
	animation = aMoving;
	vx = -1;
}

void Ship::update() {
	animation->update();
	x += vx;
}