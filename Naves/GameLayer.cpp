#include "GameLayer.h"
#include "Game.h"

#include <unordered_set>
#include <fstream>

GameLayer::GameLayer() {
	init();
}

void GameLayer::init() {
	space = new Space(1);
	background = new Background("res/fondo_2.png", WIDTH * 0.5, HEIGHT * 0.5);

	tiles.clear();
	enemies.clear();
	projectiles.clear();

	points = 0;
	textPoints = new Text("0", WIDTH * .92f, HEIGHT * .04f);
	backgroundPoints = new Actor("res/icono_puntos.png", WIDTH * .85f, HEIGHT * .05f, 24, 24);

	loadMap("res/1.txt");
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
			space->addDynamicActor(newProjectile);
		}
	}

	player->moveX(controlMoveX);
	player->moveY(controlMoveY);
}

void GameLayer::update()
{
	player->update();
	calculateScroll();

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
				deleteProjectiles.emplace(projectile);
				enemy->impacted();
				points++;
				textPoints->content = std::to_string(points);
			}
		}
	}
	for (auto const& enemy : enemies) {
		if (enemy->state == State::Dead) {
			deleteEnemies.emplace(enemy);
		}
	}
	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
		space->removeDynamicActor(delEnemy);
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
	}
	deleteProjectiles.clear();

}

void GameLayer::draw()
{
	background->draw();
	for (auto const& tile : tiles) {
		tile->draw(scrollX);
	}

	for (auto const& enemy : enemies) {
		enemy->draw(scrollX);
	}

	for (auto const& projectile : projectiles) {
		projectile->draw(scrollX);
	}

	player->draw(scrollX);

	backgroundPoints->draw();
	textPoints->draw();

	SDL_RenderPresent(Game::getRenderer());
}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			Game::getInstance().loopActive = false;
			break;
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

void GameLayer::loadMap(std::string name) {
	std::ifstream file(name);
	int row = 0;
	std::string line;

	while (std::getline(file, line)) {
		mapWidth = line.size();
		for (int column = 0; column < line.size(); column++) {
			int x = 40 / 2 + column * 40;
			int y = 32 + row * 32;
			loadMapObject(line[column], x, y);
			std::cout << line[column];
		}
		std::cout << std::endl;
		row++;
	}
}

void GameLayer::loadMapObject(char character, int x, int y) {
	switch (character) {
	case 'E': {
		Enemy* enemy = new Enemy(x, y);
		enemy->y -= enemy->height / 2;
		enemies.emplace_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case '1':
		player = new Player(x, y);
		player->y -= player->height / 2;
		space->addDynamicActor(player);
		break;
	case '#': {
		Tile* tile = new Tile("res/bloque_tierra.png", x, y);
		tile->y -= tile->height / 2;
		tiles.emplace_back(tile);
		space->addStaticActor(tile);
		break;
	}
	}
}

void GameLayer::calculateScroll() {
	if (player->x > WIDTH * .3f
		|| player->x < mapWidth - WIDTH * .3f) {

		if (player->x - scrollX < WIDTH * .3f) {
			scrollX = player->x - WIDTH * .3f;
		}
		if (player->x - scrollX > WIDTH * .7f) {
			scrollX = player->x - WIDTH * .7f;
		}

	}
}