#pragma once

#include "Layer.h"
#include "Background.h"

class WinLayer :
	public Layer
{
public:
	WinLayer();
	void init() override;
	void processControls() override;
	void draw() override;

	void keysToControls(SDL_Event event) override;
	void mouseToControls(SDL_Event event) override;
	void gamepadToControls(SDL_Event event) override;

private:
	bool controlContinue = false;

	Background* background;
};