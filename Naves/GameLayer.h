#pragma once

#include <list>

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Text.h"
#include "Tile.h"
#include "Space.h"
#include "Pad.h"
#include "Item.h"
#include "SquashedEnemy.h"

class GameLayer : public Layer
{
public:
	GameLayer();

	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;

	void loadMap(std::string name);
	void loadMapObject(char character, int x, int y);
	void calculateScroll();

	void keysToControls(SDL_Event event) override;
	void mouseToControls(SDL_Event event) override;
	void gamepadToControls(SDL_Event event) override;

	Player* player;
	Background* background;
	Actor* backgroundPoints;
	int points;
	Text* textPoints;

	Actor* backgroundItems;
	int itemCounter;
	Text* textItems;

	Pad* pad;
	Actor* buttonJump;
	Actor* buttonShoot;

	std::list<Tile*> tiles;
	std::list<Enemy*> enemies;
	std::list<SquashedEnemy*> squashedEnemies;
	std::list<Projectile*> projectiles;
	std::list<Item*> items;

	bool controlShoot = false;
	int controlMoveX = 0;
	int controlMoveY = 0;

	int newEnemyTime = 0;

	Space* space;

	float scrollX = 0;
	float scrollY = 0;
	int mapWidth = 0;
	int mapHeight = 0;
};