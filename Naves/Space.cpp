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
		actor->sweep(staticActors);
	}
}