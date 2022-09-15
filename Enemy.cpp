#include "Enemy.h"

Enemy::Enemy(float x, float y) :Actor("res/enemigo.png", x, y, 36, 40) {
	vx = -1;
}
void Enemy::update() {
	x = x + vx;
}