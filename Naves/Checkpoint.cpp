#include "Checkpoint.h"

Checkpoint::Checkpoint(float x, float y) :Actor("res/checkpoint.png", x, y, 32, 32), animation(new Animation("res/checkpoint.png", width, height, 263, 32, 6, 9)) {

}

void Checkpoint::draw(int scrollX, int scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

void Checkpoint::update() {
	animation->update();
}