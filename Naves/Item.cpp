#include "Item.h"

Item::Item(float x, float y) :Actor("res/icono_recolectable.png", x, y, 32, 32) {
	animation = new Animation("res/recolectable.png", width, height, 256, 32, 6, 8);
}

void Item::update() {
	animation->update();
}

void Item::draw(int scrollX) {
	animation->draw(x - scrollX, y);
}