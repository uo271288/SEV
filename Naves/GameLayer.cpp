#include "GameLayer.h"
#include "Game.h"

GameLayer::GameLayer() {
	init();
}

void GameLayer::init()
{
	player = new Player(50, 50);
	background = new Background("res/fondo.png", WIDTH * 0.5, HEIGHT + 0.5);

	enemies.clear();
	projectiles.clear();
}

void GameLayer::processControls()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keysToControls(event);
	}

	if (controlShoot) {
		Projectile* newProjectile = player->shoot();
		if (newProjectile) {
			projectiles.push_back(newProjectile);
		}

		player->moveX(controlMoveX);
		player->moveY(controlMoveY);
	}
}

void GameLayer::update()
{
	player->update();

	for (auto const& enemy : enemies) {
		enemy->update();
	}

	for (auto const& projectile : projectiles) {
		projectile->update();
	}
}

void GameLayer::draw()
{
	background->draw();
	for (auto const& enemy : enemies) {
		enemy->draw();
	}

	for (auto const& projectile : projectiles) {
		projectile->draw();
	}

	player->draw();
	SDL_RenderPresent(Game::getRenderer());
}

void GameLayer::keysToControls(SDL_Event event) {

}