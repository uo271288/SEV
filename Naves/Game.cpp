#include "Game.h"
#include "GameLayer.h"

constexpr int FRAME_TIME = 1000 / 30;

Game::Game() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Error SDL_Init" << SDL_GetError() << std::endl;
	}
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) {
		std::cout << "Error Window y Renderer" << SDL_GetError() << std::endl;
	}
	SDL_SetWindowTitle(window, "Juego de Naves");
	// Escalado de imágenes de calidad 
	// https://wiki.libsdl.org/SDL_HINT_RENDER_SCALE_QUALITY
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	gameLayer = new GameLayer();

	loopActive = true; // bucle activo
	loop();
}

void Game::loop() {
	int initTick, endTick, deltaTick;

	while (loopActive) {
		initTick = SDL_GetTicks();

		gameLayer->processControls();
		gameLayer->update();
		gameLayer->draw();
		
		endTick = SDL_GetTicks();
		deltaTick = endTick - initTick;

		if (deltaTick < FRAME_TIME) {
			SDL_Delay(FRAME_TIME - deltaTick);
		}
	}
}