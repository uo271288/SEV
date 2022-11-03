#include "Enemy.h"

Enemy::Enemy(std::string idle, std::string movement, std::string die, float x, float y) :Actor(idle, x, y, 36, 40) {
	aMoving = new Animation(movement, width, height, 108, 40, 6, 3);
	aDying = new Animation(die, width, height, 280, 40, 6, 8, false);
	animation = aMoving;
	vx = -1;
	vxIntelligence = -1;
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
		if (vx == 0) {
			vxIntelligence *= -1;
			vx = vxIntelligence;
		}
		break;
	case State::Dying:
		animation = aDying;
		break;
	}
}

void Enemy::draw(int scrollX) {
	animation->draw(x - scrollX, y);
}

void Enemy::impacted() {
	state = State::Dying;
}