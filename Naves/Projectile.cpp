#include "Projectile.h"

Projectile::Projectile(float x, float y):Actor("res/disparo_jugador.png",x,y,18,6) {
	vx = 9;
}

void Projectile::update() {
	x = x + vx;
}