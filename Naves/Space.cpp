#include "Space.h"

Space::Space(float gravity) :gravity(gravity) {
	dynamicActors.clear();
	staticActors.clear();
}

void Space::update() {
	for (auto const& actor : dynamicActors) {
		actor->vy += gravity;

		if (actor->vy > 20) {
			actor->vy = 20;
		}

		actor->hasCollisionDown = false;

		updateMoveRight(actor);
		updateMoveLeft(actor);
		updateMoveTop(actor);
		updateMoveDown(actor);
	}
}

void Space::updateMoveRight(Actor* dynamicActor) {

}

void Space::updateMoveLeft(Actor* dynamicActor) {

}

void Space::updateMoveTop(Actor* dynamicActor) {

}

void Space::updateMoveDown(Actor* dynamicActor) {

}