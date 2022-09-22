#include "Enemy.h"

Enemy::Enemy(float x, float y) :Actor("res/enemigo.png", x, y, 36, 40) {
	aMoving = new Animation("res/enemigo_movimiento.png", width, height, 108, 40, 6, 3);
	animation = aMoving;
	vx = -1;
}
void Enemy::update() {
	animation->update();
	x = x + vx;
}

void Enemy::draw() {
	animation->draw(x, y);
}