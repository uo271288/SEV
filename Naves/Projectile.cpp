#include "Projectile.h"

Projectile::Projectile(float x, float y) :Actor("res/fireball.png", x, y, 15, 15) {
	vx = 10;
	vy = -1;
	bounce = 10;
}

void Projectile::update() {
	if (boundingBox.touchBottom) {
		y -= bounce;
		bounce /= 1.5;
		vx /= 1.1;
		vy = -0.5;
	}
	boundingBox.update(x, y);
}