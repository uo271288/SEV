#include "Player.h"

Player::Player(float x, float y) :Actor("res/jugador.png", x, y, 50, 58)
{
	aIdleRight = new Animation("res/jugador_idle_derecha.png", width, height, 320, 40, 6, 8);

	animation = aIdleRight;
	aIdleLeft = new Animation("res/jugador_idle_izquierda.png", width, height, 320, 40, 6, 8);
	aRunningRight = new Animation("res/jugador_corriendo_derecha.png", width, height, 320, 40, 6, 8);
	aRunningLeft = new Animation("res/jugador_corriendo_izquierda.png", width, height, 320, 40, 6, 8);
	aShootingRight = new Animation("res/jugador_disparando_derecha.png", width, height, 160, 40, 6, 4, false);
	aShootingLeft = new Animation("res/jugador_disparando_izquierda.png", width, height, 160, 40, 6, 4, false);
}

Projectile* Player::shoot() {
	if (shootTime == 0) {
		shootTime = shootCadence;
		state = State::Shooting;
		Projectile* projectile = new Projectile(x, y);
		if (orientation == Orientation::Left) {
			projectile->vx *= -1;
		}
		return projectile;
	}
	return nullptr;
}

void Player::update() {
	bool animationEnded = animation->update();

	if (vx > 0) {
		orientation = Orientation::Right;
	}
	else if (vx < 0) {
		orientation = Orientation::Left;
	}if (animationEnded) {
		if (state == State::Shooting) {
			state = State::Moving;
		}
	}

	switch (state)
	{
	case State::Moving:
		if (vx == 0) {
			animation = orientation == Orientation::Right ? aIdleRight : aIdleLeft;
		}
		else {
			animation = orientation == Orientation::Right ? aRunningRight : aRunningLeft;
		}
		break;
	case State::Jumping:
		break;
	case State::Dying:
		break;
	case State::Dead:
		break;
	case State::Shooting:
		animation = orientation == Orientation::Right ? aShootingRight : aShootingLeft;
		break;
	default:
		break;
	}

	if (shootTime > 0) {
		shootTime--;
	}
}

void Player::moveX(float direction) {
	vx = direction * 3;
}

void Player::moveY(float direction) {
	vy = direction * 3;
}

void Player::draw(int scrollX, int scrollY) {
	animation->draw(x - scrollX, y-scrollY);
}

void Player::jump() {
	if (boundingBox.touchBottom) {
		vy = -16;
	}
}