#include "Enemy.h"

Enemy::Enemy(std::string filename, float x, float y, int width, int height)
	: Actor(filename, x, y, width, height) {
}

void Enemy::update(){}

void Enemy::draw() {
	animation->draw(x, y);
}