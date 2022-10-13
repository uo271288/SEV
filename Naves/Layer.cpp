#include "Layer.h"
#include "Game.h"

#include <iostream>

Layer::Layer()
{
	gamepad = SDL_GameControllerOpen(0);
}

void Layer::processControls()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_CONTROLLERDEVICEADDED)
		{
			gamepad = SDL_GameControllerOpen(0);
			if (gamepad != nullptr)
			{
				std::cout << "Gamepad connected" << std::endl;
			}
			else
			{
				std::cout << "Error connecting gamepad" << std::endl;
			}
		}

		switch (event.type)
		{
		case SDL_KEYDOWN:
			inputType = InputType::Keyboard;
			break;

		case SDL_MOUSEBUTTONDOWN:
			inputType = InputType::Mouse;
			break;

		case SDL_CONTROLLERBUTTONDOWN:
		case SDL_CONTROLLERAXISMOTION:
			inputType = InputType::Gamepad;
			break;
		}

		switch (inputType)
		{
		case InputType::Keyboard:
			keysToControls(event);
			break;
		case InputType::Mouse:
			mouseToControls(event);
			break;
		case InputType::Gamepad:
			gamepadToControls(event);
			break;
		}
	}
}

void  Layer::keysToControls(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code)
		{
		case SDLK_ESCAPE:
			Game::getInstance().loopActive = false;
			break;
		case SDLK_1:
			Game::getInstance().scale();
			break;
		}
	}
}

void  Layer::mouseToControls(SDL_Event event)
{

}

void  Layer::gamepadToControls(SDL_Event event)
{

}

bool Layer::getButton(SDL_GameControllerButton button)
{
	return SDL_GameControllerGetButton(gamepad, button);
}

bool Layer::getAxis(SDL_GameControllerAxis axis)
{
	return SDL_GameControllerGetAxis(gamepad, axis);
}