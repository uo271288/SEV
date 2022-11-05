#pragma once

#include "Layer.h"
#include "Background.h"
#include "Checkpoint.h"

class LoseLayer :
	public Layer
{
public:
	LoseLayer(bool reachedCheckpoint, Checkpoint* checkpoint);
	void init() override;
	void processControls() override;
	void draw() override;

	void keysToControls(SDL_Event event) override;
	void mouseToControls(SDL_Event event) override;
	void gamepadToControls(SDL_Event event) override;

private:
	bool controlContinue = false;
	bool reachedCheckpoint;
	Checkpoint* checkpoint;

	Background* background;
};