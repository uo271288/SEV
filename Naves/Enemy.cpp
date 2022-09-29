#include "Enemy.h"

Enemy::Enemy(float x, float y) :Actor("res/enemigo.png", x, y, 36, 40) {
	aMoving = new Animation("res/enemigo_movimiento.png", width, height, 108, 40, 6, 3);
	aDying = new Animation("res/enemigo_morir.png", width, height, 280, 40, 6, 8, false);
	animation = aMoving;
	vx = -1;
}
void Enemy::update() {
	bool animationEnded = animation->update();
	if (animationEnded) {
		if (state == State::Dying) {
			state = State::Dead;
		}
	}

	switch (state)
	{
	case State::Moving:
		animation = aMoving;
		x += vx;
		break;
	case State::Dying:
		animation = aDying;
		break;
	}
}

void Enemy::draw() {
	animation->draw(x, y);
}

void Enemy::impacted() {
	state = State::Dying;
}