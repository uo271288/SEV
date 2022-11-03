#include "SquashedEnemy.h"

SquashedEnemy::SquashedEnemy(std::string idle, std::string movement, std::string die, float x, float y) :Enemy(idle, movement, die, x, y) {

}

bool SquashedEnemy::isUp(Actor* actor) {

	bool overlap = false;
	if (actor->x - actor->width / 2 <= x + width / 2
		&& actor->x + actor->width / 2 >= x - width / 2
		&& actor->y + actor->height / 2 >= y - height / 2
		&& actor->y - actor->height / 2 <= y + height / 2
		&& !actor->boundingBox.touchBottom && actor->vy > 0) {
		overlap = true;
	}
	return overlap;
}