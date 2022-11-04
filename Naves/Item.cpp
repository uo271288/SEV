#include "Item.h"

Item::Item(float x, float y, int gravity) :Actor("res/icono_recolectable.png", x, y, 32, 32), gravity(gravity), animation(new Animation("res/recolectable.png", width, height, 256, 32, 6, 8)) {

}

void Item::update() {
	animation->update();
	vy = -gravity;
}

void Item::draw(int scrollX, int scrollY) {
	animation->draw(x - scrollX, y-scrollY);
}