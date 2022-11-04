#include "PauseLayer.h"
#include "Game.h"
#include "Menulayer.h"

PauseLayer::PauseLayer(Layer* layer)
	: Layer(), layer(layer)
{
	init();
}

void PauseLayer::init() {
	background = new Background("res/mensaje_como_jugar.png", WIDTH * .5f, HEIGHT * .5f);
}

void PauseLayer::keysToControls(SDL_Event event)
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

void PauseLayer::mouseToControls(SDL_Event event)
{
	Layer::mouseToControls(event);

	float motionX = event.motion.x / Game::getInstance().scaleLower;
	float motionY = event.motion.y / Game::getInstance().scaleLower;

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		controlContinue = true;
	}
}

void PauseLayer::gamepadToControls(SDL_Event event)
{
	Layer::gamepadToControls(event);
}

void PauseLayer::processControls() {
	Layer::processControls();
	if (controlContinue) {
		controlContinue = false;
		Game::getInstance().layer = layer;
	}
}
void PauseLayer::draw() {
	background->draw();

	SDL_RenderPresent(Game::getRenderer());
}