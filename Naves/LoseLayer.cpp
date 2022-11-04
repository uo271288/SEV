#include "LoseLayer.h"
#include "Game.h"
#include "Menulayer.h"

LoseLayer::LoseLayer()
	: Layer()
{
	init();
}

void LoseLayer::init() {
	background = new Background("res/mensaje_perder.png", WIDTH * .5f, HEIGHT * .5f);
}

void LoseLayer::keysToControls(SDL_Event event)
{
	Layer::keysToControls(event);

	if (event.type == SDL_KEYDOWN)
	{
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code)
		{
		case SDLK_SPACE: // dispara
			controlContinue = true;
			break;
		}
	}
}

void LoseLayer::mouseToControls(SDL_Event event)
{
	Layer::mouseToControls(event);

	float motionX = event.motion.x / Game::getInstance().scaleLower;
	float motionY = event.motion.y / Game::getInstance().scaleLower;

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		controlContinue = true;
	}
}

void LoseLayer::gamepadToControls(SDL_Event event)
{
	Layer::gamepadToControls(event);
}

void LoseLayer::processControls() {
	Layer::processControls();
	if (controlContinue) {
		controlContinue = false;
		Game::getInstance().layer = new MenuLayer();
	}
}
void LoseLayer::draw() {
	background->draw();

	SDL_RenderPresent(Game::getRenderer());
}