#include "Player.h"

Player::Player(float x, float y) :Actor("res/jugador.png", x, y, 50, 57) 
{

}

Projectile* Player::shoot() {
	if (shootTime == 0) {
		shootTime = shootCadence;
		return new Projectile(x, y);
	}
	return nullptr;
}

void Player::update() {
	if (shootTime > 0) {
		shootTime--;
	}
	x = x + vx;
	y = y + vy;
}

void Player::moveX(float direction) {
	vx = direction * 3;
}

void Player::moveY(float direction) {
	vy = direction * 3;
}

void Player::draw() {

}