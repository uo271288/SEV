#include "WinLayer.h"
#include "Game.h"
#include "Menulayer.h"

WinLayer::WinLayer()
	: Layer()
{
	init();
}

void WinLayer::init() {
	background = new Background("res/mensaje_ganar.png", WIDTH * .5f, HEIGHT * .5f);
}

void WinLayer::keysToControls(SDL_Event event)
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

void WinLayer::mouseToControls(SDL_Event event)
{
	Layer::mouseToControls(event);

	float motionX = event.motion.x / Game::getInstance().scaleLower;
	float motionY = event.motion.y / Game::getInstance().scaleLower;

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		controlContinue = true;
	}
}

void WinLayer::gamepadToControls(SDL_Event event)
{
	Layer::gamepadToControls(event);
}

void WinLayer::processControls() {
	Layer::processControls();
	if (controlContinue) {
		controlContinue = false;
		Game::getInstance().layer = new MenuLayer();
	}
}
void WinLayer::draw() {
	background->draw();

	SDL_RenderPresent(Game::getRenderer());
}