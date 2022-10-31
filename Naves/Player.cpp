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

void Player::changeShip(int ship) {
	if (ship == 1) {
		shootCadence = 30;
		speed = 3.;
		texture = Game::getTexture("res/jugador.png");
	}

	if (ship == 2) {
		shootCadence = 15;
		speed = 1.5;
		texture = Game::getTexture("res/jugador2.png");
	}
}

void Player::moveX(float direction) {
	vx = direction * speed;
}

void Player::moveY(float direction) {
	vy = direction * speed;
}