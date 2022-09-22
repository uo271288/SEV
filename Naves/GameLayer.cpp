#include "GameLayer.h"
#include "Game.h"

#include <unordered_set>

GameLayer::GameLayer() {
	init();
}

void GameLayer::init()
{
	player = new Player(50, 50);
	background = new Background("res/fondo.png", WIDTH * 0.5, HEIGHT * 0.5);

	enemies.clear();
	projectiles.clear();

	points = 0;
	textPoints = new Text("0", WIDTH * .92f, HEIGHT * .04f);
	backgroundPoints = new Actor("res/icono_puntos.png", WIDTH * .85f, HEIGHT * .05f, 24, 24);
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
	}

	player->moveX(controlMoveX);
	player->moveY(controlMoveY);
}

void GameLayer::update()
{
	// Generar enemigos
	newEnemyTime--;
	if (newEnemyTime <= 0) {
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		enemies.push_back(new Enemy(rX, rY));
		newEnemyTime = 110;
	}

	player->update();

	for (auto const& enemy : enemies) {
		enemy->update();
	}

	for (auto const& projectile : projectiles) {
		projectile->update();
	}

	for (auto const& enemy : enemies) {
		if (player->isOverlapping(enemy)) {
			init();
			return;
		}
	}

	std::unordered_set<Enemy*> deleteEnemies;
	std::unordered_set<Projectile*> deleteProjectiles;

	for (auto const& enemy : enemies) {
		for (auto const& projectile : projectiles) {
			if (enemy->isOverlapping(projectile)) {
				deleteEnemies.emplace(enemy);
				deleteProjectiles.emplace(projectile);

				points++;
				textPoints->content = std::to_string(points);
			}
		}
	}

	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
	}
	deleteProjectiles.clear();

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

	backgroundPoints->draw();
	textPoints->draw();

	SDL_RenderPresent(Game::getRenderer());
}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		//case SDLK_ESCAPE:
		//	Game::getInstance().loopActive = false;
		//	break;
		case SDLK_1:
			Game::getInstance().scale();
			break;
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_SPACE: // dispara
			controlShoot = true;
			break;
		}
	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_SPACE: // dispara
			controlShoot = false;
			break;
		}
	}
}