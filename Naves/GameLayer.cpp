#include "GameLayer.h"
#include "Game.h"

#include <unordered_set>
#include <fstream>

GameLayer::GameLayer()
	: Layer()
{
	init();
}

void GameLayer::init()
{
	space = new Space(GRAVITY);
	background = new Background("res/fondo_2.png", WIDTH * 0.5, HEIGHT * 0.5);

	pad = new Pad(WIDTH * .15f, HEIGHT * .8f);
	buttonJump = new Actor("res/boton_salto.png", WIDTH * .9f, HEIGHT * .55f, 100, 100);
	buttonShoot = new Actor("res/boton_disparo.png", WIDTH * .75f, HEIGHT * .83f, 100, 100);

	tiles.clear();
	enemies.clear();
	squashedEnemies.clear();
	projectiles.clear();
	items.clear();

	points = 0;
	textPoints = new Text("0", WIDTH * .92f, HEIGHT * .04f);
	backgroundPoints = new Actor("res/icono_puntos.png", WIDTH * .85f, HEIGHT * .05f, 24, 24);

	itemCounter = 0;
	textItems = new Text("0", WIDTH * .80f, HEIGHT * .04f);
	backgroundItems = new Actor("res/icono_recolectable.png", WIDTH * .72f, HEIGHT * .06f, 40, 40);

	loadMap("res/1.txt");
}

void GameLayer::processControls()
{
	Layer::processControls();

	if (controlShoot)
	{
		Projectile* newProjectile = player->shoot();
		if (newProjectile) {
			projectiles.push_back(newProjectile);
			space->addDynamicActor(newProjectile);
		}
	}

	player->moveX(controlMoveX);
	if (controlMoveY < 0)
	{
		player->jump();
	}
}

void GameLayer::update()
{
	std::unordered_set<Enemy*> deleteEnemies;
	std::unordered_set<Projectile*> deleteProjectiles;
	std::unordered_set<Item*> deleteItems;
	std::unordered_set<SquashedEnemy*> deleteSquashedEnemies;

	space->update();
	player->update();

	if (player->y > HEIGHT + 80)
	{
		init();
	}

	calculateScroll();

	for (auto const& enemy : enemies)
	{
		enemy->update();
	}

	for (auto const& enemy : squashedEnemies)
	{
		enemy->update();
	}

	for (auto const& item : items)
	{
		item->update();
	}

	for (auto const& projectile : projectiles)
	{
		projectile->update();
		if (projectile->vx == 0)
		{
			deleteProjectiles.emplace(projectile);
		}
	}

	for (auto const& enemy : enemies)
	{
		if (player->isOverlapping(enemy))
		{
			init();
			return;
		}
	}

	for (auto const& enemy : squashedEnemies)
	{
		if (enemy->isUp(player) && (enemy->state != State::Dying))
		{
			enemy->impacted();
			points++;
			textPoints->content = std::to_string(points);
		}
		if (player->isOverlapping(enemy) && (enemy->state != State::Dying))
		{
			init();
			return;
		}
	}

	for (auto const& item : items)
	{
		if (player->isOverlapping(item))
		{
			deleteItems.emplace(item);
			textItems->content = std::to_string(++itemCounter);
		}
	}

	for (auto const& enemy : enemies)
	{
		for (auto const& projectile : projectiles)
		{
			if (enemy->isOverlapping(projectile))
			{
				deleteProjectiles.emplace(projectile);
				enemy->impacted();
				points++;
				textPoints->content = std::to_string(points);
			}
		}
	}
	for (auto const& enemy : enemies)
	{
		if (enemy->state == State::Dead)
		{
			deleteEnemies.emplace(enemy);
		}
	}
	for (auto const& enemy : squashedEnemies)
	{
		if (enemy->state == State::Dead)
		{
			deleteSquashedEnemies.emplace(enemy);
		}
	}

	for (auto const& delEnemy : deleteSquashedEnemies)
	{
		squashedEnemies.remove(delEnemy);
		space->removeDynamicActor(delEnemy);
	}
	deleteSquashedEnemies.clear();

	for (auto const& delEnemy : deleteEnemies)
	{
		enemies.remove(delEnemy);
		space->removeDynamicActor(delEnemy);
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles)
	{
		projectiles.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
	}
	deleteProjectiles.clear();

	for (auto const& delItem : deleteItems)
	{
		items.remove(delItem);
		space->removeDynamicActor(delItem);
	}
	deleteItems.clear();

}

void GameLayer::draw()
{
	background->draw();
	for (auto const& tile : tiles)
	{
		tile->draw(scrollX);
	}

	for (auto const& enemy : enemies)
	{
		enemy->draw(scrollX);
	}

	for (auto const& enemy : squashedEnemies)
	{
		enemy->draw(scrollX);
	}

	for (auto const& projectile : projectiles)
	{
		projectile->draw(scrollX);
	}

	for (auto const& item : items)
	{
		item->draw(scrollX);
	}

	player->draw(scrollX);

	backgroundPoints->draw();
	textPoints->draw();

	backgroundItems->draw();
	textItems->draw();

	if (inputType == InputType::Mouse) {
		pad->draw();
		buttonJump->draw();
		buttonShoot->draw();
	}

	SDL_RenderPresent(Game::getRenderer());
}

void GameLayer::keysToControls(SDL_Event event)
{
	Layer::keysToControls(event);

	if (event.type == SDL_KEYDOWN)
	{
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code)
		{
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
	if (event.type == SDL_KEYUP)
	{
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1)
			{
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

void GameLayer::mouseToControls(SDL_Event event)
{
	Layer::mouseToControls(event);

	float motionX = event.motion.x / Game::getInstance().scaleLower;
	float motionY = event.motion.y / Game::getInstance().scaleLower;

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (pad->containsPoint(motionX, motionY))
		{
			pad->clicked = true;
			controlMoveX = pad->getOrientation(motionX);
		}

		if (buttonShoot->containsPoint(motionX, motionY))
		{
			controlShoot = true;
		}

		if (buttonJump->containsPoint(motionX, motionY))
		{
			controlMoveY = -1;
		}
	}

	if (event.type == SDL_MOUSEMOTION)
	{
		if (pad->clicked && pad->containsPoint(motionX, motionY))
		{
			controlMoveX = pad->containsPoint(motionX, motionY);

			if (controlMoveX > -20 && controlMoveX < 20)
			{
				controlMoveX = 0;
			}
		}
		else
		{
			pad->clicked = false;
			controlMoveX = 0;
		}

		if (!buttonShoot->containsPoint(motionX, motionY))
		{
			controlShoot = false;
		}

		if (!pad->containsPoint(motionX, motionY))
		{
			controlMoveY = 0;
		}
	}

	if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (pad->containsPoint(motionX, motionY))
		{
			pad->clicked = false;
			controlMoveX = 0;
		}

		if (buttonShoot->containsPoint(motionX, motionY))
		{
			controlShoot = false;
		}

		if (pad->containsPoint(motionX, motionY))
		{
			controlMoveY = 0;
		}
	}
}

void GameLayer::gamepadToControls(SDL_Event event)
{
	Layer::gamepadToControls(event);
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
		Enemy* enemy = new Enemy("res/enemigo.png", "res/enemigo_movimiento.png", "res/enemigo_morir.png", x, y);
		enemy->y -= enemy->height / 2;
		enemy->boundingBox.update(enemy->x, enemy->y);
		enemies.emplace_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case 'S': {
		SquashedEnemy* enemy = new SquashedEnemy("res/enemigo2.png", "res/enemigo2_movimiento.png", "res/enemigo2_morir.png", x, y);
		enemy->y -= enemy->height / 2;
		enemy->boundingBox.update(enemy->x, enemy->y);
		squashedEnemies.emplace_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case '1':
		player = new Player(x, y);
		player->y -= player->height / 2;
		player->boundingBox.update(player->x, player->y);
		space->addDynamicActor(player);
		break;
	case '#': {
		Tile* tile = new Tile("res/bloque_tierra.png", x, y);
		tile->y -= tile->height / 2;
		tile->boundingBox.update(tile->x, tile->y);
		tiles.emplace_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'I': {
		Item* item = new Item(x, y, GRAVITY);
		item->y -= item->height / 2;
		item->boundingBox.update(item->x, item->y);
		items.emplace_back(item);
		space->addDynamicActor(item);
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